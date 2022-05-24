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

/* Keyple Core Util */
#include "RuntimeException.h"

namespace keyple {
namespace card {
namespace generic {

using namespace keyple::core::util::cpp::exception;

/**
 * Exception when an error or a communication failure with the card or the reader occurs.
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
    TransactionException(const std::string& message) : RuntimeException(message) {}

    /**
     * Builds a new exception with the originating exception.
     *
     * @param message Message to identify the exception context.
     * @param cause The cause
     * @since 2.0.0
     */
    TransactionException(const std::string& message, const std::shared_ptr<Exception> cause)
    : RuntimeException(message, cause) {}
};

}
}
}
