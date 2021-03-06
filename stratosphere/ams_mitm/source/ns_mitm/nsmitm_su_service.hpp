#pragma once
#include <switch.h>
#include <stratosphere.hpp>

#include "../utils.hpp"

class NsSuMitmService : public IMitmServiceObject {      
    public:
        NsSuMitmService(std::shared_ptr<Service> s, u64 pid) : IMitmServiceObject(s, pid) {
            /* ... */
        }
        
        static bool ShouldMitm(u64 pid, u64 tid) {
            /* We will mitm:
             * - web applets, to facilitate hbl web browser launching.
             */
            return Utils::IsWebAppletTid(tid);
        }
        
        static void PostProcess(IMitmServiceObject *obj, IpcResponseContext *ctx);
                    
    protected:
        /* Overridden commands. */
        Result GetApplicationContentPath(OutBuffer<u8> out_path, u64 app_id, u8 storage_type);
        Result ResolveApplicationContentPath(u64 title_id, u8 storage_type);
        Result GetRunningApplicationProgramId(Out<u64> out_tid, u64 app_id);
    public:
        // DEFINE_SERVICE_DISPATCH_TABLE {
        //     // MakeServiceCommandMeta<NsSrvCmd_GetApplicationContentPath, &NsAmMitmService::GetApplicationContentPath>(),
        //     // MakeServiceCommandMeta<NsSrvCmd_ResolveApplicationContentPath, &NsAmMitmService::ResolveApplicationContentPath>(),
        //     // MakeServiceCommandMeta<NsSrvCmd_GetRunningApplicationProgramId, &NsAmMitmService::GetRunningApplicationProgramId, FirmwareVersion_600>(),
        // };
};
