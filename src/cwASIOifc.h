/** @file       cwASIOifc.h
 *  @brief      cwASIO driver API (Unix)
 *  @author     Stefan Heinzmann
 *  @version    1.0
 *  @date       2023-2024
 *  @copyright  See file LICENSE in toplevel directory
 * @addtogroup cwASIO
 *  @{
 */
#pragma once

#include "cwASIO.h"
#include <stdbool.h>


struct AsioDriver;

struct cwASIO_DriverInterface {
    void *driverLib;
    struct AsioDriver *(*instantiate)(void *);
    void (*discard)(struct AsioDriver *);
    void (*getDriverName)(struct AsioDriver *, char *);
    long (*getDriverVersion)(struct AsioDriver *);
    void (*getErrorMessage)(struct AsioDriver *, char *);
    long (*start)(struct AsioDriver *);
    long (*stop)(struct AsioDriver *);
    long (*getChannels)(struct AsioDriver *, long *, long *);
    long (*getLatencies)(struct AsioDriver *, long *, long *);
    long (*getBufferSize)(struct AsioDriver *, long *, long *, long *, long *);
    long (*canSampleRate)(struct AsioDriver *, double);
    long (*getSampleRate)(struct AsioDriver *, double *);
    long (*setSampleRate)(struct AsioDriver *, double);
    long (*getClockSources)(struct AsioDriver *, ASIOClockSource *, long *);
    long (*setClockSource)(struct AsioDriver *, long);
    long (*getSamplePosition)(struct AsioDriver *, ASIOSamples *, ASIOTimeStamp *);
    long (*getChannelInfo)(struct AsioDriver *, ASIOChannelInfo *);
    long (*createBuffers)(struct AsioDriver *, ASIOBufferInfo *, long , long , ASIOCallbacks const *);
    long (*disposeBuffers)(struct AsioDriver *);
    long (*controlPanel)(struct AsioDriver *);
    long (*future)(struct AsioDriver *, long, void *);
    long (*outputReady)(struct AsioDriver *);
};

typedef bool (cwASIOcallback)(void*, char const*, char const*, char const*);

/** Enumerate devices from /etc/cwASIO.
* An enumeration function is passed to cwASIOenumerate(), which will get called once for every entry found in the ASIO driver list.
* If the enumeration function returns with a true result, enumeration continues with the next entry, otherwise enumeration terminates.
* Three strings are passed to the enumeration function: Name, Path and Description. The latter two might be empty, if the
* corresponding registry entry is empty or absent. You might want to ignore such entries.
* @param cb Pointer to callback function
* @param context Pointer to be forwarded to callback function as its first parameter.
* @return error code, which is zero on success.
*/
int cwASIOenumerate(cwASIOcallback *cb, void *context);

/** Load the ASIO driver.
* @param key On Linux, the file path of the driver to load.
* @param ifc Pointer to the driver interface to be initialized.
* @return an error code when unsuccessful, zero on success.
*/
long cwASIOload(char const *key, struct cwASIO_DriverInterface *ifc);

/** Unload the ASIO driver.
* @param ifc Pointer to the driver interface that was initialized by cwASIOload()
*/
void cwASIOunload(struct cwASIO_DriverInterface *ifc);

/** @}*/
