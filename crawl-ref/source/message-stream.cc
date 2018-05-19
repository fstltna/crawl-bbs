#include "AppHdr.h"

#include "libutil.h" // deleteAll
#include "message.h"

#include <iostream>
#include <streambuf>

namespace msg
{
    mpr_stream_buf msbuf(MSGCH_PLAIN);
    ostream stream(&msbuf);
    vector<ostream*> stream_ptrs;
    vector<mpr_stream_buf*> stream_buffers;
    capitalisation cap(true), nocap(false);

    ostream& streams(msg_channel_type chan)
    {
        ASSERT(chan >= 0
               && static_cast<unsigned int>(chan) < stream_ptrs.size());
        return *stream_ptrs[chan];
    }

    void initialise_mpr_streams()
    {
        for (int i = 0; i < NUM_MESSAGE_CHANNELS; ++i)
        {
            mpr_stream_buf* pmsb =
                new mpr_stream_buf(static_cast<msg_channel_type>(i));
            ostream* pos = new ostream(pmsb);
            (*pos) << nounitbuf;
            stream_ptrs.push_back(pos);
            stream_buffers.push_back(pmsb);
        }
        stream << nounitbuf;
    }

    void deinitialise_mpr_streams()
    {
        deleteAll(stream_ptrs);
        deleteAll(stream_buffers);
    }

    setparam::setparam(int param)
        : m_param(param)
    {}

    capitalisation::capitalisation(bool capital)
        : m_cap(capital)
    {}

    mpr_stream_buf::mpr_stream_buf(msg_channel_type chan) :
        internal_count(0), param(0), muted(false), capitalise(true),
        channel(chan)
    {}

    void mpr_stream_buf::set_param(int p)
    {
        param = p;
    }

    void mpr_stream_buf::set_muted(bool m)
    {
        muted = m;
    }

    void mpr_stream_buf::set_capitalise(bool c)
    {
        capitalise = c;
    }

    // again, can be improved
    int mpr_stream_buf::overflow(int c)
    {
        if (muted)
            return 0;

        if (c == '\n')
        {
            // null-terminate and print the string
            internal_buf[internal_count] = 0;
            if (capitalise)
                mprf(channel, param, "%s", internal_buf);
            else
                mprf_nocap(channel, param, "%s", internal_buf);

            internal_count = 0;

            // reset to defaults (param changing and capitalisation aren't
            // sticky, but muting is).
            set_param(0);
            set_capitalise(true);
        }
        else
            internal_buf[internal_count++] = c;

        if (internal_count + 3 > INTERNAL_LENGTH)
        {
            mprf(MSGCH_ERROR, "oops, hit overflow");
            internal_count = 0;
            return streambuf::traits_type::eof();
        }
        return 0;
    }
}

ostream& operator<<(ostream& os, const msg::setparam& sp)
{
    msg::mpr_stream_buf* ps = dynamic_cast<msg::mpr_stream_buf*>(os.rdbuf());
    ps->set_param(sp.m_param);
    return os;
}

ostream& operator<<(ostream& os, const msg::capitalisation& cap)
{
    msg::mpr_stream_buf* ps = dynamic_cast<msg::mpr_stream_buf*>(os.rdbuf());
    ps->set_capitalise(cap.m_cap);
    return os;
}
