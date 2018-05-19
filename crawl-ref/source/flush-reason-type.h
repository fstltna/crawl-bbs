#pragma once

enum flush_reason_type
{
    FLUSH_ON_FAILURE,                  // spell/ability failed to cast
    FLUSH_BEFORE_COMMAND,              // flush before getting a command
    FLUSH_ON_MESSAGE,                  // flush when printing a message
    FLUSH_ON_WARNING_MESSAGE,          // flush on MSGCH_WARN messages
    FLUSH_ON_DANGER_MESSAGE,           // flush on MSGCH_DANGER messages
    FLUSH_ON_PROMPT,                   // flush on MSGCH_PROMPT messages
    FLUSH_ON_UNSAFE_YES_OR_NO_PROMPT,  // flush when !safe set to yesno()
    FLUSH_LUA,                         // flush when Lua wants to flush
    FLUSH_KEY_REPLAY_CANCEL,           // flush when key replay is cancelled
    FLUSH_ABORT_MACRO,                 // something wrong with macro being
                                       // processed, so stop it
    FLUSH_REPLAY_SETUP_FAILURE,        // setup for key replay failed
    FLUSH_REPEAT_SETUP_DONE,           // command repeat done manipulating
                                       // the macro buffer
    NUM_FLUSH_REASONS
};
