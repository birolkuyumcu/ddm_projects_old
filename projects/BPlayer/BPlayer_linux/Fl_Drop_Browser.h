#ifndef FL_DROPBROWSER_H
#define FL_DROPBROWSER_H

#include <FL/Fl_Hold_Browser.H>

class Fl_Drop_Browser : public Fl_Hold_Browser
{
   public:
      Fl_Drop_Browser(int X, int Y, int W, int H, const char *L = 0)
         : Fl_Hold_Browser(X, Y, W, H, L)
      {
//         labeltype(FL_NO_LABEL);
//         box(FL_NO_BOX);
//         clear_visible_focus();
      }

      int handle(int e)
      {
         switch(e)
         {
            case FL_DND_ENTER:
               // Indicate that DND events this widget wants DND events
            return 1;

            case FL_DND_RELEASE:
               // Indicate that this widget accepts the DND Release event
               // FL_PASTE event will follow
               return 1;

            case FL_DND_LEAVE:
               // Dunno. Perhaps undo an changes to the widget or cursor
               // that could be applied in DND_ENTER?
               return 1;

            case FL_DND_DRAG:
               return 1;

            case FL_PASTE:
               // If there is a callback registered, call it.
               // The callback must access Fl::event_text() to
               // get the string or file path that was dropped.
               if(callback())
                  do_callback();

               return 1;
         }

         return Fl_Hold_Browser::handle(e);
      }
};
#endif

