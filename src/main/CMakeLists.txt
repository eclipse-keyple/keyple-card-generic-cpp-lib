#/*************************************************************************************************
# * Copyright (c) 2023 Calypso Networks Association https://calypsonet.org/                       *
# *                                                                                               *
# * See the NOTICE file(s) distributed with this work for additional information regarding        *
# * copyright ownership.                                                                          *
# *                                                                                               *
# * This program and the accompanying materials are made available under the terms of the Eclipse *
# * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                 *
# *                                                                                               *
# * SPDX-License-Identifier: EPL-2.0                                                              *
# *************************************************************************************************/

SET(LIBRARY_NAME keyplecardgenericcpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLECARDGENERIC_EXPORT")

ADD_LIBRARY(

    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/ApduRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CardRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CardSelectorAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CardTransactionManagerAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardResourceProfileExtensionAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardSelectionAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericCardSelectionRequestAdapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GenericExtensionService.cpp 
)

TARGET_INCLUDE_DIRECTORIES(

    ${LIBRARY_NAME}

    PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}
)

TARGET_LINK_LIBRARIES(
    
    ${LIBRARY_NAME} 
    
    PUBLIC
    
    CalypsoNet::TerminalCard
    Keyple::ServiceResource
    Keyple::Util
)

ADD_LIBRARY(Keyple::CardGeneric ALIAS ${LIBRARY_NAME})
