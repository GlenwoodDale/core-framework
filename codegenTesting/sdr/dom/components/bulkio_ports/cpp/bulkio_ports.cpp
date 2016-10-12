/**************************************************************************

    This is the component code. This file contains the child class where
    custom functionality can be added to the component. Custom
    functionality to the base class can be extended here. Access to
    the ports can also be done from this class

**************************************************************************/

#include "bulkio_ports.h"

PREPARE_LOGGING(bulkio_ports_i)

bulkio_ports_i::bulkio_ports_i(const char *uuid, const char *label) :
    bulkio_ports_base(uuid, label)
{
    setPropertyChangeListener("mqd", this, &bulkio_ports_i::mqdChanged);
}

bulkio_ports_i::~bulkio_ports_i()
{
}

void bulkio_ports_i::mqdChanged (const std::string& id)
{
    dataShortIn->setMaxQueueDepth(mqd);
    mqd = dataShortIn->getMaxQueueDepth();
}


/***********************************************************************************************

    Basic functionality:

        The service function is called by the serviceThread object (of type ProcessThread).
        This call happens immediately after the previous call if the return value for
        the previous call was NORMAL.
        If the return value for the previous call was NOOP, then the serviceThread waits
        an amount of time defined in the serviceThread's constructor.
        
    SRI:
        To create a StreamSRI object, use the following code:
        	stream_id = "";
	    	sri = BULKIO::StreamSRI();
	    	sri.hversion = 1;
	    	sri.xstart = 0.0;
	    	sri.xdelta = 0.0;
	    	sri.xunits = BULKIO::UNITS_TIME;
	    	sri.subsize = 0;
	    	sri.ystart = 0.0;
	    	sri.ydelta = 0.0;
	    	sri.yunits = BULKIO::UNITS_NONE;
	    	sri.mode = 0;
	    	sri.streamID = this->stream_id.c_str();

	Time:
	    To create a PrecisionUTCTime object, use the following code:
	        struct timeval tmp_time;
	        struct timezone tmp_tz;
	        gettimeofday(&tmp_time, &tmp_tz);
	        double wsec = tmp_time.tv_sec;
	        double fsec = tmp_time.tv_usec / 1e6;;
	        BULKIO::PrecisionUTCTime tstamp = BULKIO::PrecisionUTCTime();
	        tstamp.tcmode = BULKIO::TCM_CPU;
	        tstamp.tcstatus = (short)1;
	        tstamp.toff = 0.0;
	        tstamp.twsec = wsec;
	        tstamp.tfsec = fsec;
        
    Ports:

        Data is passed to the serviceFunction through the getPacket call (BULKIO only).
        The dataTransfer class is a port-specific class, so each port implementing the
        BULKIO interface will have its own type-specific dataTransfer.

        The argument to the getPacket function is a floating point number that specifies
        the time to wait in seconds. A zero value is non-blocking. A negative value
        is blocking.

        Each received dataTransfer is owned by serviceFunction and *MUST* be
        explicitly deallocated.

        To send data using a BULKIO interface, a convenience interface has been added 
        that takes a std::vector as the data input

        NOTE: If you have a BULKIO dataSDDS port, you must manually call 
              "port->updateStats()" to update the port statistics when appropriate.

        Example:
            // this example assumes that the component has two ports:
            //  A provides (input) port of type BULKIO::dataShort called short_in
            //  A uses (output) port of type BULKIO::dataFloat called float_out
            // The mapping between the port and the class is found
            // in the component base class header file

            BULKIO_dataShort_In_i::dataTransfer *tmp = short_in->getPacket(-1);
            if (not tmp) { // No data is available
                return NOOP;
            }

            std::vector<float> outputData;
            outputData.resize(tmp->dataBuffer.size());
            for (unsigned int i=0; i<tmp->dataBuffer.size(); i++) {
                outputData[i] = (float)tmp->dataBuffer[i];
            }

            // NOTE: You must make at least one valid pushSRI call
            if (tmp->sriChanged) {
                float_out->pushSRI(tmp->SRI);
            }
            float_out->pushPacket(outputData, tmp->T, tmp->EOS, tmp->streamID);

            delete tmp; // IMPORTANT: MUST RELEASE THE RECEIVED DATA BLOCK
            return NORMAL;

        Interactions with non-BULKIO ports are left up to the component developer's discretion

    Properties:
        
        Properties are accessed directly as member variables. For example, if the
        property name is "baudRate", it may be accessed within member functions as
        "baudRate". Unnamed properties are given a generated name of the form
        "prop_n", where "n" is the ordinal number of the property in the PRF file.
        Property types are mapped to the nearest C++ type, (e.g. "string" becomes
        "std::string"). All generated properties are declared in the base class
        (bulkio_ports_base).
    
        Simple sequence properties are mapped to "std::vector" of the simple type.
        Struct properties, if used, are mapped to C++ structs defined in the
        generated file "struct_props.h". Field names are taken from the name in
        the properties file; if no name is given, a generated name of the form
        "field_n" is used, where "n" is the ordinal number of the field.
        
        Example:
            // This example makes use of the following Properties:
            //  - A float value called scaleValue
            //  - A boolean called scaleInput
              
            if (scaleInput) {
                dataOut[i] = dataIn[i] * scaleValue;
            } else {
                dataOut[i] = dataIn[i];
            }
            
        A callback method can be associated with a property so that the method is
        called each time the property value changes.  This is done by calling 
        setPropertyChangeListener(<property name>, this, &bulkio_ports_i::<callback method>)
        in the constructor.
            
        Example:
            // This example makes use of the following Properties:
            //  - A float value called scaleValue
            
        //Add to bulkio_ports.cpp
        bulkio_ports_i::bulkio_ports_i(const char *uuid, const char *label) :
            bulkio_ports_base(uuid, label)
        {
            setPropertyChangeListener("scaleValue", this, &bulkio_ports_i::scaleChanged);
        }

        void bulkio_ports_i::scaleChanged(const std::string& id){
            std::cout << "scaleChanged scaleValue " << scaleValue << std::endl;
        }
            
        //Add to bulkio_ports.h
        void scaleChanged(const std::string&);
        
        
************************************************************************************************/
int bulkio_ports_i::serviceFunction()
{
    bulkio::InCharPort::dataTransfer *charDT = dataCharIn->getPacket(0.0);
    if(charDT){
        dataCharOut->pushPacket(charDT->dataBuffer, charDT->T, charDT->EOS, charDT->streamID);
        delete charDT;
    }

    bulkio::InDoublePort::dataTransfer *doubleDT = dataDoubleIn->getPacket(0.0);
    if(doubleDT){
        dataDoubleOut->pushPacket(doubleDT->dataBuffer, doubleDT->T, doubleDT->EOS, doubleDT->streamID);
        delete doubleDT;
    }

    bulkio::InFloatPort::dataTransfer *floatDT = dataFloatIn->getPacket(0.0);
    if(floatDT){
        dataFloatOut->pushPacket(floatDT->dataBuffer, floatDT->T, floatDT->EOS, floatDT->streamID);
        delete floatDT;
    }

    bulkio::InLongPort::dataTransfer *longDT = dataLongIn->getPacket(0.0);
    if(longDT){
        dataLongOut->pushPacket(longDT->dataBuffer, longDT->T, longDT->EOS, longDT->streamID);
        delete longDT;
    }

    bulkio::InOctetPort::dataTransfer *octetDT = dataOctetIn->getPacket(0.0);
    if(octetDT){
        dataOctetOut->pushPacket(octetDT->dataBuffer, octetDT->T, octetDT->EOS, octetDT->streamID);
        delete octetDT;
    }

    bulkio::InShortPort::dataTransfer *shortDT = dataShortIn->getPacket(0.0);
    if(shortDT){
        dataShortOut->pushPacket(shortDT->dataBuffer, shortDT->T, shortDT->EOS, shortDT->streamID);
        delete shortDT;
    }

    bulkio::InULongPort::dataTransfer *ulongDT = dataUlongIn->getPacket(0.0);
    if(ulongDT){
        dataUlongOut->pushPacket(ulongDT->dataBuffer, ulongDT->T, ulongDT->EOS, ulongDT->streamID);
        delete ulongDT;
    }

    bulkio::InUShortPort::dataTransfer *ushortDT = dataUshortIn->getPacket(0.0);
    if(ushortDT){
        dataUshortOut->pushPacket(ushortDT->dataBuffer, ushortDT->T, ushortDT->EOS, ushortDT->streamID);
        delete ushortDT;
    }

    bulkio::InXMLPort::dataTransfer *xmlDT = dataXMLIn->getPacket(0.0);
    if(xmlDT){
        dataXMLOut->pushPacket((xmlDT->dataBuffer).c_str(), xmlDT->EOS, xmlDT->streamID);
        delete xmlDT;
    }

    bulkio::InFilePort::dataTransfer *fileDT = dataFileIn->getPacket(0.0);
    if(fileDT){
        dataFileOut->pushPacket((fileDT->dataBuffer).c_str(), fileDT->T, fileDT->EOS, fileDT->streamID);
        delete fileDT;
    }

    bulkio::InLongLongPort::dataTransfer *longLongDT = dataLongLongIn->getPacket(0.0);
    if(longLongDT){
        dataLongLongOut->pushPacket(longLongDT->dataBuffer, longLongDT->T, longLongDT->EOS, longLongDT->streamID);
        delete longLongDT;
    }

    bulkio::InULongLongPort::dataTransfer *ulongLongDT = dataUlongLongIn->getPacket(0.0);
    if(ulongLongDT){
        dataUlongLongOut->pushPacket(ulongLongDT->dataBuffer, ulongLongDT->T, ulongLongDT->EOS, ulongLongDT->streamID);
        delete ulongLongDT;
    }

    return NORMAL;
}
