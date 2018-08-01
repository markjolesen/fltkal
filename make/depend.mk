$(OBJ)/flprintf.o: ../src/flprintf.c ../src/flstring.h ../fl/export.h \
 ../src/config.h
$(OBJ)/flstring.o: ../src/flstring.c ../src/flstring.h ../fl/export.h \
 ../src/config.h
$(OBJ)/numsort.o: ../src/numsort.c ../fl/typesplt.h ../fl/filename.h \
 ../fl/export.h
$(OBJ)/scandir.o: ../src/scandir.c ../src/config.h
$(OBJ)/abort.o: ../src/abort.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h
$(OBJ)/add_idle.o: ../src/add_idle.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h
$(OBJ)/adjuster.o: ../src/adjuster.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/adjuster.h ../fl/valuator.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../src/arrowfas.h ../src/arrowmed.h \
 ../src/arrowslo.h
$(OBJ)/arc.o: ../src/arc.cxx ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/img.h ../fl/fl_enums.h \
 ../fl/widget.h ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/box.o: ../src/box.cxx ../fl/widget.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/fl.h ../fl/export.h \
 ../fl/fl_utf8.h ../fl/box.h
$(OBJ)/boxoval.o: ../src/boxoval.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/boxshado.o: ../src/boxshado.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/boxtype.o: ../src/boxtype.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/config.h
$(OBJ)/browser_.o: ../src/browser_.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/widget.h ../fl/fl.h ../fl/browser_.h \
 ../fl/group.h ../fl/widget.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/browser.o: ../src/browser.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/browser.h ../fl/browser_.h ../fl/group.h ../fl/widget.h ../fl/fl.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/img.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h ../src/config.h ../fl/fl_math.h \
 ../fl/browserh.h ../fl/browser.h ../fl/browserm.h ../fl/browserl.h
$(OBJ)/browserk.o: ../src/browserk.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/fl_enums.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/browserk.h ../fl/browser_.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/fl.h
$(OBJ)/browserl.o: ../src/browserl.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/browser.h ../fl/browser_.h ../fl/group.h \
 ../fl/widget.h ../fl/fl.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/img.h ../fl/fl_utf8.h
$(OBJ)/btn.o: ../src/btn.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btn.h ../fl/widget.h ../fl/fl.h ../fl/group.h ../fl/win.h \
 ../fl/imgbit.h ../fl/img.h ../fl/btnrad.h ../fl/btn.h ../fl/btntog.h
$(OBJ)/btnk.o: ../src/btnk.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h ../fl/widget.h ../fl/fl.h
$(OBJ)/btnlt.o: ../src/btnlt.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnlt.h ../fl/btn.h ../fl/widget.h ../fl/fl.h ../fl/btnradlt.h \
 ../fl/btnlt.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/btnmenu.o: ../src/btnmenu.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnmenu.h ../fl/menu_.h ../fl/widget.h ../fl/fl.h ../fl/menuitem.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/btnret.o: ../src/btnret.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnret.h ../fl/btn.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/btnro.o: ../src/btnro.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnro.h ../fl/btnlt.h ../fl/btn.h ../fl/widget.h ../fl/fl.h \
 ../fl/btnradro.h ../fl/btnro.h
$(OBJ)/btnrpt.o: ../src/btnrpt.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/btnrpt.h ../fl/fl.h ../fl/btn.h ../fl/widget.h
$(OBJ)/chart.o: ../src/chart.cxx ../fl/fl_math.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/chart.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h ../src/config.h
$(OBJ)/choice.o: ../src/choice.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/choice.h ../fl/menu_.h ../fl/widget.h ../fl/fl.h ../fl/menuitem.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h ../src/config.h
$(OBJ)/clock.o: ../src/clock.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/clock.h ../fl/widget.h ../fl/fl.h ../fl/clockrnd.h ../fl/clock.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/colorch.o: ../src/colorch.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/colorch.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/box.h \
 ../fl/btnret.h ../fl/btn.h ../fl/choice.h ../fl/menu_.h ../fl/menuitem.h \
 ../fl/img.h ../fl/inpvalue.h ../fl/valuator.h ../fl/input.h \
 ../fl/input_.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h ../fl/win.h
$(OBJ)/colorfn.o: ../src/colorfn.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/winsngl.h ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/colorfn.h ../src/config.h
$(OBJ)/compose.o: ../src/compose.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/counter.o: ../src/counter.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/counter.h ../fl/valuator.h ../fl/widget.h ../fl/fl.h \
 ../fl/counters.h ../fl/counter.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/cursor.o: ../src/cursor.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../src/drvwin.h ../fl/winovlay.h \
 ../fl/windbl.h ../fl/win.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../src/curnone.xpm ../src/cursors/crossh.xpm ../src/cursors/e.xpm \
 ../src/cursors/fleur.xpm ../src/cursors/help.xpm ../src/cursors/nesw.xpm \
 ../src/cursors/ne.xpm ../src/cursors/ns.xpm ../src/cursors/nwse.xpm \
 ../src/cursors/nw.xpm ../src/cursors/n.xpm ../src/cursors/pointer.xpm \
 ../src/cursors/se.xpm ../src/cursors/sw.xpm ../src/cursors/s.xpm \
 ../src/cursors/text.xpm ../src/cursors/wait.xpm ../src/cursors/we.xpm \
 ../src/cursors/w.xpm
$(OBJ)/curve.o: ../src/curve.cxx ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/img.h ../fl/fl_enums.h \
 ../fl/widget.h ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/dial.o: ../src/dial.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/dial.h ../fl/valuator.h ../fl/widget.h ../fl/fl.h ../fl/dialfill.h \
 ../fl/dial.h ../fl/dialline.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/diamond.o: ../src/diamond.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/display.o: ../src/display.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/dlghelp.o: ../src/dlghelp.cxx ../src/../fl/dlghelp.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/windbl.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/btn.h ../fl/input.h ../fl/input_.h ../fl/box.h ../fl/helpview.h \
 ../fl/group.h ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../fl/filename.h ../fl/imgshare.h ../src/flstring.h ../src/config.h \
 ../fl/fl_ask.h
$(OBJ)/drawpix.o: ../src/drawpix.cxx ../src/cfg_lib.h ../src/config.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../src/drvsys.h ../fl/filename.h \
 ../fl/pref.h ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h
$(OBJ)/drvcopy.o: ../src/drvcopy.cxx ../fl/drvcopy.h ../fl/widgsurf.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h \
 ../fl/win.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h
$(OBJ)/drvdev.o: ../src/drvdev.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/cfg_lib.h ../src/config.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/drvgr.o: ../src/drvgr.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/cfg_lib.h ../src/config.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/drvscr.h \
 ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/textbuf.h ../fl/fl_draw.h ../fl/drvimg.h \
 ../fl/widgsurf.h ../fl/win.h ../fl/group.h ../fl/imgshare.h \
 ../fl/fl_math.h ../fl/platform.h ../fl/allegro4.h
$(OBJ)/drvimg.o: ../src/drvimg.cxx ../fl/drvimg.h ../fl/widgsurf.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h \
 ../fl/win.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/img.h ../fl/imgshare.h ../fl/drvgr.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/drvscr.o: ../src/drvscr.cxx ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/export.h ../fl/export.h ../src/drvscr.h ../fl/fl_types.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h \
 ../fl/platform.h ../fl/allegro4.h ../fl/win.h ../fl/group.h \
 ../fl/input.h ../fl/input_.h ../src/drvwin.h ../fl/winovlay.h \
 ../fl/windbl.h ../fl/win.h ../fl/drvimg.h ../fl/widgsurf.h \
 ../fl/imgshare.h ../fl/box.h ../fl/tooltip.h ../fl/widget.h
$(OBJ)/drvsys.o: ../src/drvsys.cxx ../src/drvsys.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/filename.h ../fl/pref.h ../fl/iconfile.h \
 ../fl/fl.h ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/drvwin.o: ../src/drvwin.cxx ../src/drvwin.h ../fl/export.h ../fl/win.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/winovlay.h ../fl/windbl.h \
 ../fl/win.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h
$(OBJ)/engraved.o: ../src/engraved.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/filebr.o: ../src/filebr.cxx ../fl/filebr.h ../fl/browser.h \
 ../fl/browser_.h ../fl/group.h ../fl/widget.h ../fl/fl_enums.h \
 ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h ../fl/fl.h \
 ../fl/export.h ../fl/fl_utf8.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/fl.h ../fl/img.h ../fl/iconfile.h \
 ../fl/filename.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h ../src/config.h
$(OBJ)/filech2.o: ../src/filech2.cxx ../fl/filech.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/windbl.h ../fl/win.h ../fl/group.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/choice.h ../fl/menu_.h \
 ../fl/menuitem.h ../fl/btnmenu.h ../fl/btn.h ../fl/pref.h ../fl/tile.h \
 ../fl/group.h ../fl/filebr.h ../fl/browser.h ../fl/browser_.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/iconfile.h \
 ../fl/filename.h ../fl/box.h ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h \
 ../fl/inpfile.h ../fl/input.h ../fl/input_.h ../fl/btnret.h \
 ../fl/fl_ask.h ../src/drvsys.h ../fl/filename.h ../fl/platform.h \
 ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h ../fl/imgshare.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/filech.o: ../src/filech.cxx ../src/../fl/filech.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/windbl.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/choice.h ../fl/menu_.h ../fl/menuitem.h ../fl/btnmenu.h \
 ../fl/btn.h ../fl/pref.h ../fl/tile.h ../fl/group.h ../fl/filebr.h \
 ../fl/browser.h ../fl/browser_.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/iconfile.h ../fl/filename.h ../fl/box.h \
 ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h ../fl/inpfile.h ../fl/input.h \
 ../fl/input_.h ../fl/btnret.h ../fl/fl_ask.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/filechn.o: ../src/filechn.cxx ../fl/filechn.h ../fl/export.h \
 ../fl/filech.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/windbl.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/choice.h ../fl/menu_.h ../fl/menuitem.h \
 ../fl/btnmenu.h ../fl/btn.h ../fl/pref.h ../fl/tile.h ../fl/group.h \
 ../fl/filebr.h ../fl/browser.h ../fl/browser_.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/iconfile.h ../fl/filename.h \
 ../fl/box.h ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h ../fl/inpfile.h \
 ../fl/input.h ../fl/input_.h ../fl/btnret.h ../fl/fl_ask.h
$(OBJ)/filedir.o: ../src/filedir.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../fl/filename.h ../fl/export.h ../fl/typesplt.h \
 ../fl/filech.h ../fl/fl.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/windbl.h ../fl/win.h ../fl/group.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/choice.h ../fl/menu_.h \
 ../fl/menuitem.h ../fl/btnmenu.h ../fl/btn.h ../fl/pref.h ../fl/tile.h \
 ../fl/group.h ../fl/filebr.h ../fl/browser.h ../fl/browser_.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/iconfile.h \
 ../fl/filename.h ../fl/box.h ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h \
 ../fl/inpfile.h ../fl/input.h ../fl/input_.h ../fl/btnret.h \
 ../fl/fl_ask.h
$(OBJ)/filefltk.o: ../src/filefltk.cxx ../fl/filechn.h ../fl/export.h \
 ../fl/filech.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/windbl.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/choice.h ../fl/menu_.h ../fl/menuitem.h \
 ../fl/btnmenu.h ../fl/btn.h ../fl/pref.h ../fl/tile.h ../fl/group.h \
 ../fl/filebr.h ../fl/browser.h ../fl/browser_.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/iconfile.h ../fl/filename.h \
 ../fl/box.h ../fl/btnk.h ../fl/btnlt.h ../fl/btn.h ../fl/inpfile.h \
 ../fl/input.h ../fl/input_.h ../fl/btnret.h ../fl/fl_ask.h \
 ../fl/iconfile.h ../src/drvsys.h ../fl/filename.h
$(OBJ)/fl_arg.o: ../src/fl_arg.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/tooltip.h \
 ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h ../src/config.h
$(OBJ)/fl_ask.o: ../src/fl_ask.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/fl_ask.h \
 ../fl/box.h ../fl/widget.h ../fl/fl.h ../fl/btn.h ../fl/btnret.h \
 ../fl/btn.h ../fl/win.h ../fl/group.h ../fl/imgbit.h ../fl/img.h \
 ../fl/input.h ../fl/input_.h ../fl/inphid.h ../fl/input.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../src/drvscr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/texted.h \
 ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../fl/fl_draw.h
$(OBJ)/fl_box.o: ../src/fl_box.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/fl_boxro.o: ../src/fl_boxro.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/fl_color.o: ../src/fl_color.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/fl_cmap.h
$(OBJ)/fl.o: ../src/fl.cxx ../src/cfg_lib.h ../src/config.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/platform.h ../fl/fl_types.h \
 ../fl/allegro4.h ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../fl/group.h ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h \
 ../fl/textbuf.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h \
 ../fl/win.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../fl/tooltip.h ../fl/widget.h ../fl/fl_draw.h ../src/flstring.h
$(OBJ)/fl_draw.o: ../src/fl_draw.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/fl_enums.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/flstring.h ../src/config.h ../fl/fl_math.h
$(OBJ)/fl_font.o: ../src/fl_font.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/fl_enums.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/fl_gleam.o: ../src/fl_gleam.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/fl_grab.o: ../src/fl_grab.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/fl_gtk.o: ../src/fl_gtk.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/fl_rect.o: ../src/fl_rect.cxx ../fl/platform.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/fl_uri.o: ../src/fl_uri.cxx ../src/cfg_lib.h ../src/config.h \
 ../fl/filename.h ../fl/export.h ../fl/typesplt.h ../fl/fl.h \
 ../fl/export.h ../fl/fl_utf8.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/pref.h ../src/flstring.h
$(OBJ)/fl_utf8.o: ../src/fl_utf8.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/fl_utf8.h \
 ../src/utf8priv.h ../src/xutf8/wcwidth.c
$(OBJ)/fnabs.o: ../src/fnabs.cxx ../fl/filename.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../src/drvsys.h ../fl/pref.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/fnexpand.o: ../src/fnexpand.cxx ../src/drvsys.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/filename.h ../fl/pref.h
$(OBJ)/fnext.o: ../src/fnext.cxx ../src/drvsys.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/filename.h ../fl/pref.h
$(OBJ)/fnisdir.o: ../src/fnisdir.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../src/drvsys.h ../fl/fl.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/filename.h ../fl/pref.h
$(OBJ)/fnlist.o: ../src/fnlist.cxx ../fl/filename.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../src/drvsys.h ../fl/pref.h \
 ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/fnmatch.o: ../src/fnmatch.cxx ../fl/filename.h ../fl/export.h \
 ../fl/typesplt.h
$(OBJ)/fnsetext.o: ../src/fnsetext.cxx ../fl/filename.h ../fl/export.h \
 ../fl/typesplt.h ../src/flstring.h ../fl/export.h ../src/config.h
$(OBJ)/group.o: ../src/group.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../src/drvwin.h ../fl/win.h \
 ../fl/imgbit.h ../fl/img.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h \
 ../fl/rect.h ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/helpview.o: ../src/helpview.cxx ../fl/helpview.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h ../fl/widget.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/filename.h ../fl/imgshare.h ../fl/win.h ../fl/fl.h \
 ../fl/group.h ../fl/fl_utf8.h ../fl/filename.h ../src/flstring.h \
 ../src/config.h ../fl/fl_math.h
$(OBJ)/hotspot.o: ../src/hotspot.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h
$(OBJ)/icon2fil.o: ../src/icon2fil.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../src/flstring.h ../fl/export.h ../src/config.h \
 ../fl/fl_math.h ../fl/iconfile.h ../fl/fl.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/fl_enums.h ../fl/imgshare.h ../fl/img.h \
 ../fl/widget.h ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgbit.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/filename.h
$(OBJ)/iconfile.o: ../src/iconfile.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../src/flstring.h ../fl/export.h ../src/config.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/iconfile.h \
 ../fl/fl.h ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/iconize.o: ../src/iconize.cxx ../fl/win.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h
$(OBJ)/imgbit.o: ../src/imgbit.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/widget.h \
 ../fl/menuitem.h
$(OBJ)/imgbmp.o: ../src/imgbmp.cxx ../fl/imgbmp.h ../fl/img.h ../fl/fl_enums.h \
 ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h ../fl/widget.h \
 ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/fl_utf8.h ../fl/fl.h
$(OBJ)/imgcore.o: ../src/imgcore.cxx ../fl/imgshare.h ../fl/img.h \
 ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/widget.h ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/imgbmp.h \
 ../fl/imggif.h ../fl/imgpix.h ../fl/imgjpeg.h ../fl/imgpng.h \
 ../fl/imgpnm.h ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/img.o: ../src/img.cxx ../src/cfg_lib.h ../src/config.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/widget.h ../fl/menuitem.h ../src/flstring.h
$(OBJ)/imggif.o: ../src/imggif.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/imggif.h ../fl/imgpix.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/imgjpeg.o: ../src/imgjpeg.cxx ../fl/imgjpeg.h ../fl/img.h \
 ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/widget.h ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h \
 ../fl/imgshare.h ../fl/fl_utf8.h ../fl/fl.h ../src/config.h
$(OBJ)/imgpix.o: ../src/imgpix.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../fl/widget.h ../fl/menuitem.h ../src/flstring.h ../src/config.h
$(OBJ)/imgpng.o: ../src/imgpng.cxx ../src/config.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../fl/imgpng.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/imgshare.h \
 ../fl/fl_utf8.h
$(OBJ)/imgpnm.o: ../src/imgpnm.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/imgpnm.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/fl_utf8.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/imgread.o: ../src/imgread.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/imgshare.o: ../src/imgshare.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../src/flstring.h ../fl/export.h ../src/config.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_enums.h \
 ../fl/imgshare.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/imgxbm.h \
 ../fl/imgbit.h ../fl/imgxpm.h ../fl/imgpix.h ../fl/pref.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/imgtiled.o: ../src/imgtiled.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/imgtiled.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/win.h ../fl/group.h ../fl/imgbit.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/imgxbm.o: ../src/imgxbm.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/imgxbm.h ../fl/imgbit.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/imgxpm.o: ../src/imgxpm.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/imgxpm.h ../fl/imgpix.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/inpcho.o: ../src/inpcho.cxx ../fl/inpcho.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/input.h \
 ../fl/input_.h ../fl/btnmenu.h ../fl/menu_.h ../fl/menuitem.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/inpfile.o: ../src/inpfile.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/inpfile.h \
 ../fl/input.h ../fl/input_.h ../fl/widget.h ../fl/fl.h ../fl/win.h \
 ../fl/group.h ../fl/imgbit.h ../fl/img.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/input_.o: ../src/input_.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/input_.h ../fl/widget.h ../fl/fl.h ../fl/win.h ../fl/group.h \
 ../fl/imgbit.h ../fl/img.h ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../fl/fl_draw.h \
 ../fl/fl_ask.h ../fl/fl_math.h ../fl/fl_utf8.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/input.o: ../src/input.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../src/drvscr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/texted.h \
 ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../fl/input.h \
 ../fl/input_.h ../fl/fl_draw.h ../fl/fl_ask.h ../src/flstring.h \
 ../src/config.h ../fl/inpfloat.h ../fl/input.h ../fl/inpint.h \
 ../fl/inpmulti.h ../fl/output.h ../fl/outmulti.h ../fl/output.h \
 ../fl/inphid.h
$(OBJ)/inpvalue.o: ../src/inpvalue.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/inpvalue.h ../fl/valuator.h ../fl/widget.h \
 ../fl/fl.h ../fl/input.h ../fl/input_.h ../fl/group.h ../fl/fl_math.h
$(OBJ)/labelm.o: ../src/labelm.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/widget.h ../fl/fl.h ../fl/menuitem.h ../fl/widget.h ../fl/img.h \
 ../fl/labelm.h
$(OBJ)/labeltyp.o: ../src/labeltyp.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/widget.h ../fl/fl.h ../fl/group.h ../fl/widget.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/input_.h
$(OBJ)/latin1.o: ../src/latin1.cxx ../src/cfg_lib.h ../src/config.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h \
 ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/export.h ../fl/img.h ../fl/fl_enums.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/fl.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../src/flstring.h
$(OBJ)/macroman.o: ../src/macroman.cxx ../src/cfg_lib.h ../src/config.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h \
 ../fl/typesplt.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/export.h ../fl/img.h ../fl/fl_enums.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/drvsys.h ../fl/fl.h ../fl/filename.h ../fl/pref.h \
 ../src/flstring.h
$(OBJ)/menuadd.o: ../src/menuadd.cxx ../fl/menu_.h ../fl/widget.h \
 ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/menuitem.h ../fl/img.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/menubar.o: ../src/menubar.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/menubar.h ../fl/menu_.h ../fl/widget.h ../fl/fl.h ../fl/menuitem.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/menu_.o: ../src/menu_.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/menu_.h ../fl/widget.h ../fl/fl.h ../fl/menuitem.h ../fl/img.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/menu.o: ../src/menu.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvwin.h ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/winmenu.h \
 ../fl/winsngl.h ../fl/menu_.h ../fl/menuitem.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/menuglob.o: ../src/menuglob.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/menu_.h ../fl/widget.h ../fl/fl.h \
 ../fl/menuitem.h ../fl/img.h
$(OBJ)/outvalue.o: ../src/outvalue.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/outvalue.h ../fl/valuator.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/overlay.o: ../src/overlay.cxx ../fl/platform.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/drvscr.h ../fl/texted.h ../fl/textdsp.h \
 ../fl/fl_draw.h ../fl/group.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/pack.o: ../src/pack.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/pack.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/plastic.o: ../src/plastic.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/pref.o: ../src/pref.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvsys.h ../fl/filename.h ../fl/pref.h ../fl/plugin.h \
 ../fl/pref.h ../fl/fl_utf8.h ../src/flstring.h ../src/config.h
$(OBJ)/progress.o: ../src/progress.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/progress.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/roller.o: ../src/roller.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/roller.h ../fl/valuator.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/scrlarea.o: ../src/scrlarea.cxx ../src/drvwin.h ../fl/export.h \
 ../fl/win.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/winovlay.h ../fl/windbl.h \
 ../fl/win.h
$(OBJ)/scrlbar.o: ../src/scrlbar.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/scroll.o: ../src/scroll.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/imgtiled.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/scroll.h \
 ../fl/group.h ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/scrxywh.o: ../src/scrxywh.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h \
 ../src/config.h
$(OBJ)/set_font.o: ../src/set_font.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/drvscr.h ../fl/texted.h ../fl/textdsp.h \
 ../fl/fl_draw.h ../fl/group.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/textbuf.h ../src/flstring.h ../src/config.h
$(OBJ)/shortcut.o: ../src/shortcut.cxx ../src/cfg_lib.h ../src/config.h \
 ../fl/fl.h ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/widget.h \
 ../fl/fl.h ../fl/btn.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h
$(OBJ)/slider.o: ../src/slider.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/slider.h ../fl/valuator.h ../fl/widget.h ../fl/fl.h ../fl/slfill.h \
 ../fl/slider.h ../fl/slhz.h ../fl/slhzfill.h ../fl/slhznice.h \
 ../fl/slnice.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/slvalue.o: ../src/slvalue.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/slvalue.h ../fl/slider.h ../fl/valuator.h ../fl/widget.h \
 ../fl/fl.h ../fl/slhzval.h ../fl/slvalue.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/fl_math.h
$(OBJ)/spinner.o: ../src/spinner.cxx ../fl/spinner.h ../fl/fl_enums.h \
 ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h ../fl/group.h \
 ../fl/widget.h ../fl/fl_enums.h ../fl/fl.h ../fl/export.h \
 ../fl/fl_utf8.h ../fl/input.h ../fl/input_.h ../fl/btnrpt.h ../fl/btn.h
$(OBJ)/symbols.o: ../src/symbols.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/fl_math.h \
 ../src/flstring.h ../src/config.h
$(OBJ)/syscolor.o: ../src/syscolor.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h \
 ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h ../fl/textbuf.h ../src/drvsys.h ../fl/filename.h \
 ../fl/pref.h ../fl/fl_draw.h ../fl/platform.h ../fl/allegro4.h \
 ../fl/win.h ../fl/group.h ../fl/fl_math.h ../fl/fl_utf8.h \
 ../src/flstring.h ../src/config.h ../fl/imgtiled.h ../src/tile.xpm
$(OBJ)/table.o: ../src/table.cxx ../fl/table.h ../fl/group.h ../fl/widget.h \
 ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/scroll.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/fl.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/tablerow.o: ../src/tablerow.cxx ../fl/tablerow.h ../fl/table.h \
 ../fl/group.h ../fl/widget.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/fl.h ../fl/export.h \
 ../fl/fl_utf8.h ../fl/scroll.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h
$(OBJ)/tabs.o: ../src/tabs.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/tabs.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/tooltip.h ../fl/widget.h
$(OBJ)/terminal.o: ../src/terminal.cxx ../fl/terminal.h ../fl/export.h \
 ../fl/textdsp.h ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../src/flstring.h \
 ../src/config.h
$(OBJ)/textbuf.o: ../src/textbuf.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../src/flstring.h ../fl/export.h ../src/config.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_enums.h \
 ../fl/textbuf.h ../fl/fl_ask.h
$(OBJ)/textdsp.o: ../src/textdsp.cxx ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../src/flstring.h ../fl/export.h ../src/config.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/textbuf.h ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../src/drvscr.h \
 ../fl/texted.h ../fl/textdsp.h
$(OBJ)/texted.o: ../src/texted.cxx ../src/flstring.h ../fl/export.h \
 ../src/config.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h ../src/drvscr.h \
 ../fl/fl_types.h ../fl/fl_ask.h
$(OBJ)/tile.o: ../src/tile.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/tile.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/win.h \
 ../fl/group.h ../fl/imgbit.h ../fl/img.h ../fl/rect.h ../fl/widget.h
$(OBJ)/tooltip.o: ../src/tooltip.cxx ../fl/tooltip.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/widget.h ../fl/fl.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/widget.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/winmenu.h ../fl/winsngl.h \
 ../fl/win.h ../fl/group.h ../src/drvsys.h ../fl/filename.h ../fl/pref.h \
 ../src/drvwin.h ../fl/win.h ../fl/winovlay.h ../fl/windbl.h
$(OBJ)/treearr.o: ../src/treearr.cxx ../fl/treearr.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/treeitem.h ../fl/widget.h ../fl/fl.h ../fl/img.h \
 ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/treepref.h
$(OBJ)/tree.o: ../src/tree.cxx ../fl/tree.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../fl/treeitem.h ../fl/widget.h ../fl/treearr.h ../fl/treepref.h \
 ../fl/pref.h
$(OBJ)/treeitem.o: ../src/treeitem.cxx ../fl/widget.h ../fl/fl_enums.h \
 ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h ../fl/fl.h \
 ../fl/export.h ../fl/fl_utf8.h ../fl/treeitem.h ../fl/fl.h ../fl/img.h \
 ../fl/widget.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/treearr.h ../fl/treepref.h \
 ../fl/tree.h ../fl/group.h ../fl/scrlbar.h ../fl/slider.h \
 ../fl/valuator.h
$(OBJ)/treepref.o: ../src/treepref.cxx ../src/cfg_lib.h ../src/config.h \
 ../src/drvsys.h ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/filename.h ../fl/pref.h ../fl/imgpix.h ../fl/img.h ../fl/widget.h \
 ../fl/fl.h ../fl/treepref.h
$(OBJ)/valuator.o: ../src/valuator.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/valuator.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_math.h ../src/flstring.h ../src/config.h
$(OBJ)/vertex.o: ../src/vertex.cxx ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/export.h ../fl/export.h ../fl/img.h ../fl/fl_enums.h \
 ../fl/fl_types.h ../fl/typesplt.h ../fl/widget.h ../fl/fl.h \
 ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../fl/fl.h ../fl/fl_math.h
$(OBJ)/visual.o: ../src/visual.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../src/drvscr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h \
 ../fl/fl_types.h ../fl/texted.h ../fl/textdsp.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h ../fl/widget.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h ../fl/group.h \
 ../fl/scrlbar.h ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/widget.o: ../src/widget.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/widget.h ../fl/fl.h ../fl/group.h ../fl/widget.h ../fl/tooltip.h \
 ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../src/flstring.h ../src/config.h
$(OBJ)/widgsurf.o: ../src/widgsurf.cxx ../fl/widgsurf.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h ../fl/win.h \
 ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h ../fl/drvgr.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../fl/platform.h ../fl/fl_types.h \
 ../fl/allegro4.h ../fl/imgshare.h ../src/drvwin.h ../fl/winovlay.h \
 ../fl/windbl.h ../fl/win.h ../src/drvscr.h ../fl/texted.h \
 ../fl/textdsp.h ../fl/fl_draw.h ../fl/group.h ../fl/scrlbar.h \
 ../fl/slider.h ../fl/valuator.h ../fl/textbuf.h
$(OBJ)/win.o: ../src/win.cxx ../src/config.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h \
 ../fl/win.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h \
 ../fl/imgrgb.h ../fl/tooltip.h ../fl/widget.h ../fl/fl_draw.h \
 ../fl/fl_enums.h ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h \
 ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../src/flstring.h
$(OBJ)/windbl.o: ../src/windbl.cxx ../fl/fl.h ../fl/export.h ../fl/typesplt.h \
 ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../fl/windbl.h ../fl/win.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h ../src/drvwin.h ../fl/winovlay.h \
 ../fl/windbl.h
$(OBJ)/winmenu.o: ../src/winmenu.cxx ../fl/winmenu.h ../fl/winsngl.h ../fl/win.h \
 ../fl/fl.h ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h \
 ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h ../src/drvwin.h \
 ../fl/win.h ../fl/winovlay.h ../fl/windbl.h
$(OBJ)/winovlay.o: ../src/winovlay.cxx ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drvwin.h ../fl/win.h
$(OBJ)/winscr.o: ../src/winscr.cxx ../fl/win.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../src/drvwin.h ../fl/winovlay.h ../fl/windbl.h ../fl/win.h
$(OBJ)/winsngl.o: ../src/winsngl.cxx ../fl/winsngl.h ../fl/win.h ../fl/fl.h \
 ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h \
 ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h ../fl/widget.h \
 ../fl/fl.h ../fl/imgbit.h ../fl/img.h
$(OBJ)/wizard.o: ../src/wizard.cxx ../fl/wizard.h ../fl/group.h ../fl/widget.h \
 ../fl/fl_enums.h ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/win.h ../fl/fl.h \
 ../fl/imgbit.h ../fl/img.h ../fl/fl_draw.h ../fl/fl_enums.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/aldrvcp.o: ../src/drivers/allegro4/aldrvcp.cxx \
 ../src/drivers/allegro4/aldrvcp.h ../fl/drvcopy.h ../fl/widgsurf.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h \
 ../fl/win.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h
$(OBJ)/aldrvgr.o: ../src/drivers/allegro4/aldrvgr.cxx \
 ../src/drivers/allegro4/aldrvgr.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h ../fl/img.h \
 ../fl/fl_enums.h ../fl/fl_types.h ../fl/typesplt.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../src/drivers/allegro4/imgconv.h ../fl/fl.h
$(OBJ)/aldrvimg.o: ../src/drivers/allegro4/aldrvimg.cxx \
 ../src/drivers/allegro4/aldrvimg.h ../fl/drvimg.h ../fl/widgsurf.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h \
 ../fl/win.h ../fl/fl.h ../fl/typesplt.h ../fl/fl_utf8.h ../fl/fl_types.h \
 ../fl/fl_enums.h ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h \
 ../fl/img.h ../fl/img.h ../fl/imgshare.h ../fl/drvgr.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/fl_draw.h ../fl/fl_enums.h
$(OBJ)/aldrvscr.o: ../src/drivers/allegro4/aldrvscr.cxx \
 ../src/drivers/allegro4/aldrvscr.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../src/drivers/allegro4/wm.h \
 ../fl/win.h ../fl/fl.h ../fl/export.h ../fl/fl_utf8.h ../fl/fl_enums.h \
 ../fl/group.h ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drivers/allegro4/timeout.h ../src/drivers/allegro4/ticker.h \
 ../src/drivers/allegro4/ticks.h ../src/drivers/allegro4/aldrvwin.h \
 ../fl/platform.h ../fl/fl_types.h ../fl/allegro4.h
$(OBJ)/aldrvsys.o: ../src/drivers/allegro4/aldrvsys.cxx \
 ../src/drivers/allegro4/aldrvsys.h ../fl/widget.h ../fl/fl_enums.h \
 ../fl/export.h ../fl/fl_types.h ../fl/typesplt.h ../fl/fl.h \
 ../fl/export.h ../fl/fl_utf8.h
$(OBJ)/aldrvwin.o: ../src/drivers/allegro4/aldrvwin.cxx \
 ../src/drivers/allegro4/aldrvwin.h ../fl/fl_enums.h ../fl/export.h \
 ../fl/fl_types.h ../fl/typesplt.h ../src/drivers/allegro4/aldrvgr.h \
 ../fl/drvgr.h ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h \
 ../fl/img.h ../fl/fl_enums.h ../fl/widget.h ../fl/fl.h ../fl/fl_utf8.h \
 ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../src/drivers/allegro4/imgconv.h ../fl/fl.h ../fl/platform.h \
 ../fl/fl_types.h ../fl/allegro4.h ../fl/win.h ../fl/group.h
$(OBJ)/algfx.o: ../src/drivers/allegro4/algfx.cxx \
 ../src/drivers/allegro4/algfx.h
$(OBJ)/imgconv.o: ../src/drivers/allegro4/imgconv.cxx \
 ../src/drivers/allegro4/imgconv.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h ../fl/img.h \
 ../fl/fl_enums.h ../fl/fl_types.h ../fl/typesplt.h ../fl/widget.h \
 ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h ../fl/imgpix.h \
 ../fl/imgrgb.h ../fl/fl.h
$(OBJ)/rgb16.o: ../src/drivers/allegro4/rgb16.cxx
$(OBJ)/rgb24cb.o: ../src/drivers/allegro4/rgb24cb.cxx ../fl/drvgr.h \
 ../fl/drvdev.h ../fl/plugin.h ../fl/pref.h ../fl/export.h ../fl/export.h \
 ../fl/img.h ../fl/fl_enums.h ../fl/fl_types.h ../fl/typesplt.h \
 ../fl/widget.h ../fl/fl.h ../fl/fl_utf8.h ../fl/imgbit.h ../fl/img.h \
 ../fl/imgpix.h ../fl/imgrgb.h
$(OBJ)/rgb24.o: ../src/drivers/allegro4/rgb24.cxx
$(OBJ)/rgb32.o: ../src/drivers/allegro4/rgb32.cxx
$(OBJ)/rgb8.o: ../src/drivers/allegro4/rgb8.cxx
$(OBJ)/timeout.o: ../src/drivers/allegro4/timeout.cxx \
 ../src/drivers/allegro4/timeout.h ../src/drivers/allegro4/ticker.h \
 ../src/drivers/allegro4/ticks.h ../fl/fl.h ../fl/export.h \
 ../fl/typesplt.h ../fl/fl_utf8.h ../fl/export.h ../fl/fl_types.h \
 ../fl/fl_enums.h
$(OBJ)/wm.o: ../src/drivers/allegro4/wm.cxx ../src/drivers/allegro4/wm.h \
 ../fl/win.h ../fl/fl.h ../fl/export.h ../fl/typesplt.h ../fl/fl_utf8.h \
 ../fl/export.h ../fl/fl_types.h ../fl/fl_enums.h ../fl/group.h \
 ../fl/widget.h ../fl/fl.h ../fl/imgbit.h ../fl/img.h \
 ../src/drivers/allegro4/aldrvwin.h ../fl/fl_enums.h \
 ../src/drivers/allegro4/aldrvgr.h ../fl/drvgr.h ../fl/drvdev.h \
 ../fl/plugin.h ../fl/pref.h ../fl/img.h ../fl/imgpix.h ../fl/imgrgb.h \
 ../src/drivers/allegro4/algfx.h ../fl/platform.h ../fl/fl_types.h \
 ../fl/allegro4.h
$(OBJ)/xbm.o: ../src/drivers/allegro4/xbm.cxx
$(OBJ)/case.o: ../src/xutf8/case.c ../src/xutf8/../utf8priv.h \
 ../src/xutf8/headers/case.h
$(OBJ)/spacing.o: ../src/xutf8/spacing.c ../src/xutf8/../utf8priv.h \
 ../src/xutf8/headers/spacing.h
$(OBJ)/wcwidth.o: ../src/xutf8/wcwidth.c
