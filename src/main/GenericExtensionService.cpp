/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#include "GenericExtensionService.h"

/* Keyple Card Generic */
#include "GenericCardSelectionAdapter.h"
#include "GenericCardResourceProfileExtensionAdapter.h"

/* Calypsonet Terminal Card */
#include "CardApiProperties.h"

/* Calypsonet Terminal Reader */
#include "ReaderApiProperties.h"

/* Keyple Core Common */
#include "CommonApiProperties.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card;
using namespace calypsonet::terminal::reader;
using namespace keyple::core::common;

std::shared_ptr<GenericExtensionService> GenericExtensionService::mInstance;

GenericExtensionService::GenericExtensionService() {}

std::shared_ptr<GenericExtensionService> GenericExtensionService::getInstance()
{
    if (mInstance == nullptr) {
        mInstance = std::shared_ptr<GenericExtensionService>(new GenericExtensionService());
    }

    return mInstance;
}

std::shared_ptr<GenericCardSelection> GenericExtensionService::createCardSelection()
{
    return std::make_shared<GenericCardSelectionAdapter>();
}

std::shared_ptr<CardTransactionManager> GenericExtensionService::createCardTransaction(
    std::shared_ptr<CardReader> reader, std::shared_ptr<SmartCard> card)
{
    return std::make_shared<CardTransactionManagerAdapter>(reader, card);
}

std::shared_ptr<CardResourceProfileExtension>
    GenericExtensionService::createCardResourceProfileExtension(
        std::shared_ptr<GenericCardSelection> genericCardSelection)
{
    return std::make_shared<GenericCardResourceProfileExtensionAdapter>(genericCardSelection);
}

const std::string& GenericExtensionService::getCardApiVersion() const
{
    return CardApiProperties_VERSION;
}

const std::string& GenericExtensionService::getReaderApiVersion() const
{
    return ReaderApiProperties_VERSION;
}

const std::string& GenericExtensionService::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

}
}
}
