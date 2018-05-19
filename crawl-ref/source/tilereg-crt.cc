#include "AppHdr.h"

#ifdef USE_TILE_LOCAL

#include "tilereg-crt.h"

#include "cio.h"
#include "menu.h"
#include "tilefont.h"
#include "viewgeom.h"

CRTRegion::CRTRegion(FontWrapper *font) : TextRegion(font), m_attached_menu(nullptr)
{
}

CRTRegion::~CRTRegion()
{
    clear();
}

int CRTRegion::handle_mouse(MouseEvent &event)
{
    int ret_val = 0;
    if (m_attached_menu == nullptr)
    {
        if (event.event == MouseEvent::PRESS)
        {
            if (event.button == MouseEvent::LEFT)
                ret_val = CK_MOUSE_CLICK;
            else if (event.button == MouseEvent::RIGHT)
                ret_val = CK_MOUSE_CMD;
        }
    }
    else
        ret_val = m_attached_menu->handle_mouse(event);
    return ret_val;
}

void CRTRegion::on_resize()
{
    TextRegion::on_resize();
    crawl_view.termsz.x = mx;
    crawl_view.termsz.y = my;

    // Todo: resize attached menu
}

void CRTRegion::clear()
{
    // clear all the texts
    TextRegion::clear();
    detach_menu();
}

void CRTRegion::render()
{
    set_transform(true);

    // render all the inherited texts
    TextRegion::render();

    // render the attached menu if it exists
    if (m_attached_menu != nullptr)
        m_attached_menu->draw_menu();
}

void CRTRegion::attach_menu(PrecisionMenu* menu)
{
    detach_menu();

    m_attached_menu = menu;
}

void CRTRegion::detach_menu()
{
    // Tiles has no rights over the menu, thus the user must delete it
    // Via other means
    m_attached_menu = nullptr;
}

#endif
