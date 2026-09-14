/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#include "keyple/card/generic/GenericExtensionService.hpp"

#include "keyple/card/generic/CardTransactionManagerAdapter.hpp"
#include "keyple/card/generic/GenericCardResourceProfileExtensionAdapter.hpp"
#include "keyple/card/generic/GenericCardSelectionExtensionAdapter.hpp"
#include "keyple/core/common/CommonApiProperties.hpp"
#include "keypop/card/CardApiProperties.hpp"
#include "keypop/reader/ReaderApiProperties.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::common::CommonApiProperties_VERSION;
using keypop::card::CardApiProperties_VERSION;
using keypop::reader::ReaderApiProperties_VERSION;

std::shared_ptr<GenericExtensionService> GenericExtensionService::mInstance;

GenericExtensionService::GenericExtensionService()
{
}

std::shared_ptr<GenericExtensionService>
GenericExtensionService::getInstance()
{
    if (mInstance == nullptr) {
        mInstance = std::shared_ptr<GenericExtensionService>(
            new GenericExtensionService());
    }

    return mInstance;
}

std::shared_ptr<GenericCardSelectionExtension>
GenericExtensionService::createGenericCardSelectionExtension()
{
    return std::make_shared<GenericCardSelectionExtensionAdapter>();
}

std::shared_ptr<CardTransactionManager>
GenericExtensionService::createCardTransaction(
    std::shared_ptr<CardReader> reader, std::shared_ptr<SmartCard> card)
{
    return std::make_shared<CardTransactionManagerAdapter>(reader, card);
}

std::shared_ptr<CardResourceProfileExtension>
GenericExtensionService::createCardResourceProfileExtension(
    const std::shared_ptr<IsoCardSelector> cardSelector,
    const std::shared_ptr<GenericCardSelectionExtension>
        genericCardSelectionExtension)
{
    return std::make_shared<GenericCardResourceProfileExtensionAdapter>(
        cardSelector, genericCardSelectionExtension);
}

const std::string
GenericExtensionService::getCardApiVersion() const
{
    return CardApiProperties_VERSION;
}

const std::string
GenericExtensionService::getReaderApiVersion() const
{
    return ReaderApiProperties_VERSION;
}

const std::string
GenericExtensionService::getCommonApiVersion() const
{
    return CommonApiProperties_VERSION;
}

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
