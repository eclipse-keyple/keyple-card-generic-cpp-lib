#******************************************************************************
#* Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
#*                                                                            *
#* See the NOTICE file(s) distributed with this work for additional           *
#* information regarding copyright ownership.                                 *
#*                                                                            *
#* This program and the accompanying materials are made available under the   *
#* terms of the Eclipse Public License 2.0 which is available at              *
#* http://www.eclipse.org/legal/epl-2.0                                       *
#*                                                                            *
#* SPDX-License-Identifier: EPL-2.0                                           *
#******************************************************************************/

SET(LIBRARY_NAME keyplecardgenericcpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLECARDGENERIC_EXPORT")

INCLUDE("CMakeLists.txt.keypop-card")
INCLUDE("CMakeLists.txt.keyple-service-resource")
INCLUDE("CMakeLists.txt.keyple-util")

ADD_LIBRARY(

    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/ApduRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CardRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CardTransactionManagerAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardSelectionExtensionAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardResourceProfileExtensionAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardSelectionRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericExtensionService.cpp
)

TARGET_INCLUDE_DIRECTORIES(

    ${LIBRARY_NAME}

    PUBLIC

    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

TARGET_LINK_LIBRARIES(

    ${LIBRARY_NAME}

    PUBLIC

    Keypop::Card
    Keyple::Service::Resource
    Keyple::Util
)

ADD_LIBRARY(

    Keyple::Card::Generic

    ALIAS

    ${LIBRARY_NAME}
)
