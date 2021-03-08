#include <kern/kern_func.h>

const char block_paths[][75] = {
    "/Applications/iGameGuardian.app",
    "/private/var/mobile/Library/iGameGuardian",
    "/Library/BreakThrough",
    "/Library/LaunchDaemons/com.apple.gg.daemon.plist",
    "/private/var/db/stash",
    "/Library/PreferenceLoader/Preferences/LibertyPref.plist",
    "/Applications/Flex.app",
    "/Library/PreferenceLoader/Preferences/NoSubstitute.plist",
    "/Library/Frameworks/CydiaSubstrate.framework",
    "/usr/lib/TweakInject",
    "/usr/lib/libsubstrate.dylib",
    "/private/var/mobile/Library/Flex3",
    "/Applications/GameGemiOS.app",
    "/var/containers/Bundle/tweaksupport",
    "/private/var/containers/Bundle/tweaksupport",
    "/User",
    "/boot",
    "/lib",
    "/mnt",
    "/Applications/Cydia.app",
    "/private/var/lib",
    "/jb",
    "/private/var/mobile/Library/Caches/com.saurik.Cydia",
    "/var/mobile/Library/Caches/com.saurik.Cydia",
    "/private/etc/ssh",
    "/Library/MobileSubstrate",
    "/var/containers/Bundle/iosbinpack64",
    "/private/var/containers/Bundle/iosbinpack64",
    "/var/libexec",
    "/private/var/libexec",
    "/Applications/Sileo.app",
    "/private/var/mobile/Library/Caches/Snapshots/org.coolstar.SileoStore",
    "/private/var/mobile/Library/Preferences/org.coolstar.SileoStore.plist",
    "/Applications/Zebra.app",
    "/Library/dpkg/info/xyz.willy.zebra.list",
    "/private/var/mobile/Library/Preferences/xyz.willy.Zebra.plist",
};

int check_path(const char *p) {
    int arrsize = sizeof(block_paths) / sizeof(block_paths[0]);
    //xprintf("checking through %d paths\n", arrsize);
    for (int i = 0; i < arrsize; i++) {
	//xprintf("checking %s vs %s\n", p, block_paths[i]);
        if (_strncmp(p, block_paths[i], _strlen(block_paths[i])) == 0) {
            return 1;
        }
    }
    return 0;
}
