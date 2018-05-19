#pragma once

#include <functional>

/** Type that gives an lvalue a dynamically-scoped temporary value. An
 *  unwind_var wraps a variable or other writable lvalue, assigns it a
 *  temporary value, and restores the original (or a specified) value when
 *  the unwind_var goes out of scope or is otherwise destroyed.
 */
template <typename T>
class unwind_var
{
public:
    /** Wrap the lvalue val_ and on unwinding restore its original value. */
    unwind_var(T &val_) : val(val_), oldval(val_) { }

    /** Wrap the lvalue val_, assign it the temporary value newval, and
     *  on unwinding restore its original value.
     */
    unwind_var(T &val_, T newval) : val(val_), oldval(val_)
    {
        val = newval;
    }

    /** Wrap the lvalue val_, assign it the temporary value newval, and
     *  on unwinding assign it the value reset_to.
     */
    unwind_var(T &val_, T newval, T reset_to) : val(val_), oldval(reset_to)
    {
        val = newval;
    }

    ~unwind_var()
    {
        val = oldval;
    }

    /** Get the current (temporary) value of the wrapped lvalue. */
    T value() const
    {
        return val;
    }

    /** Get the value that will be used to restore the wrapped lvalue. */
    T original_value() const
    {
        return oldval;
    }

private:
    T &val;
    T oldval;
};

typedef unwind_var<bool> unwind_bool;

/** Type to call a function when an instance goes out of scope or is
 * otherwise destroyed.
 */
class unwinder
{
public:
    /** Construct an unwinder that calls cleanup_fn when destroyed. */
    // We templatise the parameter, rather than taking a function<>, so that
    // we can write "unwinder foo = [](){};" without running into the
    // "only one user-defined conversion at a time" rule.
    template<class Fn>
    unwinder(Fn cleanup_fn) : cleaner(cleanup_fn) { }

    ~unwinder()
    {
        if (cleaner)
            cleaner();
    }

    /** Cancel this unwinder, so that it calls nothing when destroyed. */
    void cancel()
    {
        cleaner = nullptr;
    }
private:
    function<void ()> cleaner;
};

// Preprocessor tricks, ugh.
#define CONCAT_IMPL(x, y) x##y
#define CONCAT_TOK(x, y) CONCAT_IMPL(x, y)

/** Set up a block of code to run when the current scope is exited.
 *
 * Usage: ON_UNWIND { block of code here };
 *
 * Defines a variable, with a generated name, to hold the unwinder.
 */
#define ON_UNWIND unwinder CONCAT_TOK(_gensym_uw_, __LINE__) = [&] () -> void
