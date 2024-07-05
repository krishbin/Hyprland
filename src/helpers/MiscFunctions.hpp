#pragma once

#include <optional>
#include <string>
#include <wayland-server.h>
#include "math/Math.hpp"
#include <vector>
#include <format>

struct SCallstackFrameInfo {
    void*       adr = nullptr;
    std::string desc;
};

struct SWorkspaceIDName {
    int         id = -1;
    std::string name;
};

std::string                      absolutePath(const std::string&, const std::string&);
void                             addWLSignal(wl_signal*, wl_listener*, void* pOwner, const std::string& ownerString);
void                             removeWLSignal(wl_listener*);
std::string                      escapeJSONStrings(const std::string& str);
bool                             isDirection(const std::string&);
bool                             isDirection(const char&);
SWorkspaceIDName                 getWorkspaceIDNameFromString(const std::string&);
std::optional<std::string>       cleanCmdForWorkspace(const std::string&, std::string);
float                            vecToRectDistanceSquared(const Vector2D& vec, const Vector2D& p1, const Vector2D& p2);
void                             logSystemInfo();
std::string                      execAndGet(const char*);
int64_t                          getPPIDof(int64_t pid);
int64_t                          configStringToInt(const std::string&);
Vector2D                         configStringToVector2D(const std::string&);
std::optional<float>             getPlusMinusKeywordResult(std::string in, float relative);
void                             matrixProjection(float mat[9], int w, int h, wl_output_transform tr);
double                           normalizeAngleRad(double ang);
std::vector<SCallstackFrameInfo> getBacktrace();
void                             throwError(const std::string& err);
bool                             envEnabled(const std::string& env);
int                              allocateSHMFile(size_t len);
bool                             allocateSHMFilePair(size_t size, int* rw_fd_ptr, int* ro_fd_ptr);

template <typename... Args>
[[deprecated("use std::format instead")]] std::string getFormat(std::format_string<Args...> fmt, Args&&... args) {
    // no need for try {} catch {} because std::format_string<Args...> ensures that vformat never throw std::format_error
    // because any suck format specifier will cause a compilation error
    // this is actually what std::format in stdlib does
    return std::vformat(fmt.get(), std::make_format_args(args...));
}
