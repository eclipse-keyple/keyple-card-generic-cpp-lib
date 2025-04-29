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

#include "keyple/card/generic/GenericCardSelectionExtension.hpp"
#include "keyple/card/generic/GenericCardSelectionExtensionAdapter.hpp"
#include "keyple/core/service/resource/spi/CardResourceProfileExtension.hpp"
#include "keyple/core/util/cpp/Logger.hpp"
#include "keyple/core/util/cpp/LoggerFactory.hpp"
#include "keypop/reader/CardReader.hpp"
#include "keypop/reader/ReaderApiFactory.hpp"
#include "keypop/reader/selection/IsoCardSelector.hpp"
#include "keypop/reader/selection/spi/SmartCard.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::service::resource::spi::CardResourceProfileExtension;
using keyple::core::util::cpp::Logger;
using keyple::core::util::cpp::LoggerFactory;
using keypop::reader::CardReader;
using keypop::reader::ReaderApiFactory;
using keypop::reader::selection::IsoCardSelector;
using keypop::reader::selection::spi::SmartCard;

/**
 * Implementation of CardResourceProfileExtension that provides the capability
 * to filter cards of any type.
 *
 * @since 2.0.0
 */
class GenericCardResourceProfileExtensionAdapter final
: public CardResourceProfileExtension {
public:
    /**
     * @param cardSelector An ISO card selector.
     * @param genericCardSelectionExtension The generic card selection
     * extension.
     * @since 2.0.0
     */
    GenericCardResourceProfileExtensionAdapter(
        std::shared_ptr<IsoCardSelector> cardSelector,
        std::shared_ptr<GenericCardSelectionExtension>
            genericCardSelectionExtension);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<SmartCard> matches(
        std::shared_ptr<CardReader> reader,
        std::shared_ptr<ReaderApiFactory> readerApiFactory) override;

    /**
     * {@inheritDoc}
     *
     * @since 3.1.0
     */
    std::shared_ptr<SmartCard>
    matches(std::shared_ptr<SmartCard> smartCard) override;

private:
    /**
     *
     */
    const std::unique_ptr<Logger> mLogger = LoggerFactory::getLogger(
        typeid(GenericCardResourceProfileExtensionAdapter));

    /**
     *
     */
    std::shared_ptr<GenericCardSelectionExtensionAdapter> mGenericCardSelection;

    /**
     *
     */
    std::shared_ptr<IsoCardSelector> mCardSelector;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
