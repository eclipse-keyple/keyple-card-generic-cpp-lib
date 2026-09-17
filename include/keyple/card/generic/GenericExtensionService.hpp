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

#pragma once

#include <memory>
#include <string>

#include "keyple/card/generic/KeypleCardGenericExport.hpp"
#include "keyple/core/common/KeypleCardExtension.hpp"
#include "keyple/core/service/resource/spi/CardResourceProfileExtension.hpp"
#include "keypop/genericcard/GenericCardApiFactory.hpp"
#include "keypop/genericcard/GenericCardSelectionExtension.hpp"
#include "keypop/reader/selection/IsoCardSelector.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::common::KeypleCardExtension;
using keyple::core::service::resource::spi::CardResourceProfileExtension;
using keypop::genericcard::GenericCardApiFactory;
using keypop::genericcard::GenericCardSelectionExtension;
using keypop::reader::selection::IsoCardSelector;

/**
 * Card extension service providing basic access to APDU exchange functions with
 * a card.
 *
 * @since 2.0.0
 */
class KEYPLECARDGENERIC_API GenericExtensionService final
: public KeypleCardExtension {
public:
    /**
     * Gets the unique instance of this object.
     *
     * @return A not null reference.
     */
    static std::shared_ptr<GenericExtensionService> getInstance();

    /**
     * Returns an instance of GenericCardApiFactory.
     *
     * @return A not null reference.
     * @since 4.0.0
     */
    std::shared_ptr<GenericCardApiFactory> getGenericCardApiFactory();

    /**
     * Creates an instance of CardResourceProfileExtension to be provided to the
     * keyple::core::service::resource::CardResourceService.
     *
     * <p>The provided argument defines the selection rules to be applied to the
     * card when detected by the card resource service.
     *
     * @param cardSelector The ISO card selector targeting the expected card
     *        profile.
     * @param genericCardSelectionExtension A not null generic card extension.
     * @return A not null reference.
     * @throws IllegalArgumentException If genericCardSelectionExtension is
     *         null.
     * @since 2.0.0
     */
    std::shared_ptr<CardResourceProfileExtension>
    createCardResourceProfileExtension(
        const std::shared_ptr<IsoCardSelector> cardSelector,
        const std::shared_ptr<GenericCardSelectionExtension>
            genericCardSelectionExtension);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getCardApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getReaderApiVersion() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string getCommonApiVersion() const override;

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

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
