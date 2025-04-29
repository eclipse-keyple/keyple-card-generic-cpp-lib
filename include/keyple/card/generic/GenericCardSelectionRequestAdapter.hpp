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
#include <ostream>
#include <vector>

#include "keypop/card/spi/CardRequestSpi.hpp"
#include "keypop/card/spi/CardSelectionRequestSpi.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::card::spi::CardRequestSpi;
using keypop::card::spi::CardSelectionRequestSpi;

/**
 * Implementation of CardSelectionRequestSpi.
 *
 * @since 2.0.0
 */
class GenericCardSelectionRequestAdapter final
: public CardSelectionRequestSpi {
public:
    /**
     * Builds a card selection request to open a logical channel with additional
     * APDUs to be sent after the selection step.
     *
     * @param successfulSelectionStatusWords List of successful status words.
     * @since 2.0.0
     */
    explicit GenericCardSelectionRequestAdapter(
        const std::vector<int>& successfulSelectionStatusWords);

    /**
     * {@inheritDoc}
     *
     * @since 3.0.0
     */
    const std::vector<int>& getSuccessfulSelectionStatusWords() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::shared_ptr<CardRequestSpi> getCardRequest() const override;

    /**
     * {@inheritDoc}
     *
     * @since 3.0.0
     */
    friend std::ostream& operator<<(
        std::ostream& os, const GenericCardSelectionRequestAdapter& gcsra);

    /**
     * {@inheritDoc}
     *
     * @since 3.0.0
     */
    friend std::ostream& operator<<(
        std::ostream& os,
        const std::shared_ptr<GenericCardSelectionRequestAdapter> gcsra);

private:
    /**
     *
     */
    std::vector<int> mSuccessfulSelectionStatusWords;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
