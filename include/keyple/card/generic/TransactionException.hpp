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

#include "keyple/core/util/cpp/exception/RuntimeException.hpp"

namespace keyple {
namespace card {
namespace generic {

using keyple::core::util::cpp::exception::RuntimeException;

/**
 * Exception when an error or a communication failure with the card or the
 * reader occurs.
 *
 * @since 2.0.0
 */
class TransactionException : public RuntimeException {
public:
    /**
     * Builds a new exception.
     *
     * @param message Message to identify the exception context.
     * @since 2.0.0
     */
    explicit TransactionException(const std::string& message)
    : RuntimeException(message)
    {
    }

    /**
     * Builds a new exception with the originating exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause
     * @since 2.0.0
     */
    TransactionException(
        const std::string& message, const std::shared_ptr<Exception> cause)
    : RuntimeException(message, cause)
    {
    }

    /**
     * Builds a new exception with the originating exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause
     * @since 2.0.0
     */
    TransactionException(
        const std::string& message, const std::shared_ptr<std::exception>)
    : RuntimeException(message)
    {
    }
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
