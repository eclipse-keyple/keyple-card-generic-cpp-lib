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

#pragma once

#include <memory>

/* Keyple Core Common */
#include "KeypleCardExtension.h"

/* Keyple Card Generic */
#include "CardTransactionManagerAdapter.h"
#include "GenericCardSelection.h"
#include "KeypleCardGenericExport.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"
#include "SmartCard.h"

/* Keyple Core Service */
#include "CardResourceProfileExtension.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::reader;
using namespace calypsonet::terminal::reader::selection::spi;
using namespace keyple::core::common;
using namespace keyple::core::service::resource::spi;

/**
 * Card extension service providing basic access to APDU exchange functions with a card.
 *
 * @since 2.0.0
 */
class KEYPLECARDGENERIC_API GenericExtensionService final : public KeypleCardExtension {
public:
    /**
     * Gets the unique instance of this object.
     *
     * @return A not null reference.
     */
    static std::shared_ptr<GenericExtensionService> getInstance();

    /**
     * Creates an instance of GenericCardSelection.
     *
     * @return A not null reference.
     * @since 2.0.0
     */
    std::shared_ptr<GenericCardSelection> createCardSelection();

    /**
     * Creates an instance of CardTransactionManager.
     *
     * @param reader The reader through which the card communicates.
     * @param card The initial card data provided by the selection process.
     * @return A not null reference.
     * @since 2.0.0
     */
    std::shared_ptr<CardTransactionManager> createCardTransaction(
        std::shared_ptr<CardReader> reader, std::shared_ptr<SmartCard> card);

    /**
     * Creates an instance of CardResourceProfileExtension to be provided to the {@link
     * org.eclipse.keyple.core.service.resource.CardResourceService}.
     *
     * <p>The provided argument defines the selection rules to be applied to the card when detected
     * by the card resource service.
     *
     * @param genericCardSelection A not null {@link GenericCardSelection}.
     * @return A not null reference.
     * @throw IllegalArgumentException If genericCardSelection is null.
     * @since 2.0.0
     */
    std::shared_ptr<CardResourceProfileExtension> createCardResourceProfileExtension(
        std::shared_ptr<GenericCardSelection> genericCardSelection);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getCardApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getReaderApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getCommonApiVersion() const override;

private:
    /**
     *
     */
    static std::shared_ptr<GenericExtensionService> mInstance;

    /**
     * Constructor
     */
    GenericExtensionService();
};

}
}
}
