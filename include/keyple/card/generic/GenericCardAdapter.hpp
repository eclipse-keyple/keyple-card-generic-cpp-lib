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

#include "keypop/card/CardSelectionResponseApi.hpp"
#include "keypop/card/spi/SmartCardSpi.hpp"
#include "keypop/reader/selection/spi/IsoSmartCard.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::card::CardSelectionResponseApi;
using keypop::card::spi::SmartCardSpi;
using keypop::reader::selection::spi::IsoSmartCard;

/**
 * (package-private)<br>
 * Implementation of a generic {@link SmartCard}.
 *
 * @since 2.0.0
 */
class GenericCardAdapter final : public IsoSmartCard, public SmartCardSpi {
public:
    /**
     * Constructor
     *
     * <p>Gets ATR and FCI from the CardSelectionResponseApi if they exist (both
     * are optional).
     *
     * @param cardSelectionResponse The CardSelectionResponseApi from the
     * selection process.
     */
    explicit GenericCardAdapter(
        std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::string& getPowerOnData() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::vector<std::uint8_t> getSelectApplicationResponse() const override;

private:
    /**
     *
     */
    const std::vector<std::uint8_t> mSelectApplicationResponse;

    /**
     *
     */
    const std::string mPowerOnData;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
