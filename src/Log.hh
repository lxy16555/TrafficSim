/* 
 * File:   Log.hh
 * Author: ehein6
 *
 * Created on January 26, 2015, 3:52 PM
 */

#ifndef LOG_HH
#define	LOG_HH

#include <stdio.h>
#include <inttypes.h>

#define LOG(format, ...) fprintf (stderr, format, ## __VA_ARGS__)

#endif	/* LOG_HH */

