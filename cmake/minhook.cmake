include(FetchContent)

# MinHook publishes no releases; the commit below is master at the time of
# writing, which keeps the build reproducible.
FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        8af6b4acae5a9388fd742b56fa79ece89d96f823
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(minhook)

set_target_properties(minhook PROPERTIES FOLDER "deps")
