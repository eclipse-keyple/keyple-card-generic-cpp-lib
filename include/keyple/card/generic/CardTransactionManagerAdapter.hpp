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
#include <vector>

#include "keyple/card/generic/CardTransactionManager.hpp"
#include "keyple/card/generic/ChannelControl.hpp"
#include "keypop/card/spi/ApduRequestSpi.hpp"
#include "keypop/reader/CardReader.hpp"
#include "keypop/reader/selection/spi/SmartCard.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::card::spi::ApduRequestSpi;
using keypop::reader::CardReader;
using keypop::reader::selection::spi::SmartCard;

/**
 * Implementation of CardTransactionManager.
 *
 * @since 2.0.0
 */
class CardTransactionManagerAdapter final : public CardTransactionManager {
public:
    /**
     *
     */
    static const std::string APDU_COMMAND;

    /**
     * Creates an instance of CardTransactionManager.
     *
     * @param reader The reader through which the card communicates.
     * @param card The initial card data provided by the selection process.
     * @throw IllegalArgumentException If the card resource or one of its
     *        components is null.
     * @since 2.0.0
     */
    CardTransactionManagerAdapter(
        std::shared_ptr<CardReader> reader,
        const std::shared_ptr<SmartCard> card);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager&
    prepareApdu(const std::string& apduCommand) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager&
    prepareApdu(const std::vector<uint8_t>& apduCommand) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(
        const uint8_t cla,
        const uint8_t ins,
        const uint8_t p1,
        const uint8_t p2,
        const std::vector<uint8_t>& dataIn,
        const uint8_t le) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(
        const uint8_t cla,
        const uint8_t ins,
        const uint8_t p1,
        const uint8_t p2,
        const std::vector<uint8_t>& dataIn) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::vector<uint8_t>>
    processApdusToByteArrays(const ChannelControl channelControl) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::string>
    processApdusToHexStrings(ChannelControl channelControl) override;

private:
    /**
     *
     */
    std::shared_ptr<CardReader> mReader;

    /**
     *
     */
    std::vector<std::shared_ptr<ApduRequestSpi>> mApduRequests;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
