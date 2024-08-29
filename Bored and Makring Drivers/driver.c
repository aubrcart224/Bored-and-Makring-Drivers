#include <ntddk.h>
#include <wdf.h>	


DRIVER_INITIALIZE DriverEntry; 
EVT_WDF_DRIVER_DEVICE_ADD EvtDriverDeviceAdd;
EVT_WDF_DEVICE_CONTEXT_CLEANUP UnloadDriver;	


_Use_decl_annotations_

// unload driver
void UnloadDriver(IN WDFDRIVER driver)
{
	UNREFERENCED_PARAMETER(driver);
	DbgPrint("Driver Unloaded");
}


// driver entry
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	WDF_DRIVER_CONFIG config;
	WDF_DRIVER_CONFIG_INIT(&config, EvtDriverDeviceAdd);
	config.EvtDriverUnload = UnloadDriver;
	NTSTATUS status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);

	DbgPrint("Driver loaded");

	return status;
}

// add device
NTSTATUS EvtDriverDeviceAdd(IN WDFDRIVER driver, IN PWDFDEVICE_INIT deviceInit)
{
	UNREFERENCED_PARAMETER(driver);
	WDFDEVICE device;
	NTSTATUS status = WdfDeviceCreate(&deviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);

	return status; 
}	


/*
void EvtIoDefault(IN WDFQUEUE queue, IN WDFREQUEST request)
{
	UNREFERENCED_PARAMETER(queue);
	WdfRequestComplete(request, STATUS_SUCCESS);
}
*/