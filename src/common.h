#pragma once

#include <string>
#include <memory>
#include <cstdio>
#include <locale>
#include <iostream>
#include <net/if.h>
#include <sys/inotify.h>
#include <unistd.h>

#include <php.h>
#include <zend_exceptions.h>
#include <zend_interfaces.h>
#include <zend_ini.h>

#include "common/phpvalue.h"
#include "common/zutils.h"
#include "common/zhandle.h"
#include "common/zinotify.h"
#include "common/zstdio.h"
