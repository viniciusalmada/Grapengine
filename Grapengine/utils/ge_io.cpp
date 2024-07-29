#include "utils/ge_io.hpp"

#include "core/ge_assert.hpp"

using namespace GE;

std::string IO::ReadFileToString(const std::filesystem::path& path)
{
#if !defined(GE_COVERAGE_ENABLED)
  try
  {
#endif
    GE_ASSERT_OR_RETURN(std::filesystem::exists(path),
                        {},
                        "File {} not found (pwd: {})",
                        path.string(),
                        std::filesystem::current_path().string());

    GE_ASSERT_OR_RETURN(std::filesystem::is_regular_file(path), {}, "File is not regular");

    const std::ifstream stream(path, std::ios ::in | std::ios ::binary);
    GE_ASSERT_OR_RETURN(stream.is_open(), {}, "Failed to open file for reading: {}", path.string());

    std::ostringstream out_content;
    out_content << stream.rdbuf();

    return out_content.str();
#if !defined(GE_COVERAGE_ENABLED)
  }
  catch (const std::exception& ex)
  {
    GE_ASSERT(false, "Exception found {}", ex.what());
    return {};
  }
#endif
}
