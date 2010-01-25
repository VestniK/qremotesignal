/**
 * @file message.cpp
 * @brief Message implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 25 Jan 2010
 */
#include "message.h"

using namespace qrs;

namespace qrs {
    namespace internals {
        class MessagePrivate {
        };
    }
}

Message::Message(): d(new internals::MessagePrivate) {
    mType = RemoteCall; mErrorType = Ok;
}

Message::~Message() {
    delete d;
}
