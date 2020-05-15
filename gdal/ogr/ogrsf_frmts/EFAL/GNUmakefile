

include ../../../GDALmake.opt

OBJ	=	from_mitab.o \
		ogrefaldatasource.o \
		ogrefaldriver.o \
		ogrefallayer.o \
		style_utility.o \
		ogrgeopackageutility.o

CPPFLAGS	:=	-I. -I.. -I../..  -I../generic  -I../gpkg  -I../../../gcore $(CPPFLAGS)

default:	$(O_OBJ:.o=.$(OBJ_EXT))

clean:
	rm -f *.o $(O_OBJ)

$(O_OBJ):       MIDefs.h EFAL.h EFALAPI.h EFALErrorIDs.h EFALLIB.h from_mitab.h OGREFAL.h ogrgeopackageutility.h

PLUGIN_SO	= ogr_EFAL.$(SO_EXT)

plugin:	 $(PLUGIN_SO)

$(PLUGIN_SO):	$(OBJ)
		$(LD_SHARED) $(LNK_FLAGS) $(OBJ) $(CONFIG_LIBS_INS) $(LIBS) \
		-o $(PLUGIN_SO)