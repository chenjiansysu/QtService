TEMPLATE = subdirs

SUBDIRS += service \
	plugins

plugins.depends += service

prepareRecursiveTarget(lrelease)
QMAKE_EXTRA_TARGETS += lrelease
