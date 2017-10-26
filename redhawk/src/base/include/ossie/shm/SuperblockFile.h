/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file
 * distributed with this source distribution.
 *
 * This file is part of REDHAWK core.
 *
 * REDHAWK core is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * REDHAWK core is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef REDHAWK_SHM_SUPERBLOCKFILE_H
#define REDHAWK_SHM_SUPERBLOCKFILE_H

#include <map>

#include "MappedFile.h"

namespace redhawk {

    namespace shm {

        class Superblock;

        class SuperblockFile {
        public:
            SuperblockFile(const std::string& name);
            ~SuperblockFile();

            void create();
            void open();
            void close();

            Superblock* getSuperblock(size_t offset);
            Superblock* createSuperblock(size_t bytes);

            const std::string& name() const;

        private:
            // Not copyable
            SuperblockFile(const SuperblockFile&);
            SuperblockFile& operator=(const SuperblockFile&);

            Superblock* _mapSuperblock(size_t offset);

            MappedFile _file;

            struct Header;
            Header* _header;

            typedef std::map<size_t,Superblock*> SuperblockMap;
            SuperblockMap _superblocks;
        };
    }
}

#endif // REDHAWK_SHM_SUPERBLOCKFILE_H
