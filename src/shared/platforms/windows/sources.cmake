# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

target_sources(shared-sources INTERFACE
     ${CMAKE_CURRENT_SOURCE_DIR}/shared/eventlistener.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/shared/eventlistener.h
     ${CMAKE_CURRENT_SOURCE_DIR}/shared/platforms/windows/windowscryptosettings.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/shared/platforms/windows/windowsutils.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/shared/platforms/windows/windowsutils.h
)

include(${CMAKE_CURRENT_SOURCE_DIR}/shared/signature.cmake)
