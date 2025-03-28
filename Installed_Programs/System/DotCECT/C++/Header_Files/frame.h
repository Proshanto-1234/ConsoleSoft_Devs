#include "DEVICES.HPP"
#include <stdexcept>
#define CD_ROM_HPP

#ifndef CD_DISC_STATESDEFINED
// The CD states are likely not defined, so define them NOW
#define CD_DISC_OK 0x000A; // If CD disc is OK
#define CD_DISC_READY 0x010A; // If CD disc is ready for performing operations
#define CD_ERROR_CRYPTOGRAPCHIC_ERROR 0x020A; // If the CD operation or disc has a Cryptographic error, which is random
#define CD_DISC_IN_USE 0x030A; // If the CD disc is currently in use
#define CD_DISC_ERASEING = 0x040A; // If the CD is being erased
#define CD_DISC_STATESDEFINED
 
#endif // !CD_DISC_STATESDEFINED

struct CDStatus
{
	int CD_STATUS = CD_DISC_OK;
};

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
class Device_CD_ROM : Device_StorageDevice {
protected:
	int DiskSize;
	CDStatus status;
	bool EraseDisc(FormatType type);
	bool AcessFile(char Path[]); // Accesses
	bool Failed;
public:
	bool Format() {
		throw IncorrectMethodUsedExeception("Format", 0x000E, "Erase") {}
	}

};
class IncorrectMethodUsedExeception : std::exception 
{
public:
	char MethodName[(sizeof())];
	int ReturnCode = 0xE;
	string FileName;
	string Message;
protected:
	~IncorrectMethodUsedExeception() {
		// Do nothing!
	}
	IncorrectMethodUsedExeception(char Method[]  // Method name is selected here
		,
		int returnedcode = 0 //	Default the return code to 0
		, char Suggested[]
		, string Message = "This method is NOT supposed to be performed on this object. Try using"
	) {
		FileName = "";
		ReturnCode = returnedcode;
		MethodName = Method;
	}

};
