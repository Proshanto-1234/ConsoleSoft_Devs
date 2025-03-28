#define DEVICES_HPP
#include "String.LIB"

// Class container for common storage devices
class Device_StorageDevice {
public:
	long int StorageSize;
	bool Format() {
		// Mock logics. We will delete this function (define it as NULL) in other drivers
	}
	class FileStream {
		string Name;
		string ReadContents() {}
	};
};
enum FormatType {
	Quick /* As far as we can say, A quick format make a device
		  * seem empty, but the device *MIGHT* still contain data.
		  * A Quick format *ERASES* data using the tradition quick
		  * methid. It must be used with care if the device contains
		  * personal data which is *SERCRET*
		  */,
	Full /* A full format erases and removes all data a OS can
		 * normally see. A data recovery software *MIGHT* see
		 * this data and even *MIGHT RECOVER* it. This possibility
		 * is *NOT* always gurranted, so it must be used with 
		 * caution if you might want to recover the data or if
		 * the data is important and you have *UNFORTUNATELY*
		 * entered the wrong letter
		 */,
	None // A imaginary format type which *DOESN'T* perform any formats at all. It is for flexibility
};
