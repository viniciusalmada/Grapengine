#include "utils/ge_io.hpp"

#include "core/ge_assert.hpp"

using namespace GE;

std::string IO::ReadFileToString(const std::filesystem::path& path)
{
  try
  {
    if (!std::filesystem::exists(path))
      throw std::runtime_error("File \'" + path.string() + "\' not found (pwd: " +
                               std::filesystem::current_path().string() + ")");

    if (!std::filesystem::is_regular_file(path))
      throw std::runtime_error("File is not regular");

    std::ifstream stream(path, std::ios ::in | std::ios ::binary);
    if (!stream.is_open())
      throw std::runtime_error("Failed to open file for reading: " + path.string());

    std::ostringstream out_content;
    out_content << stream.rdbuf();

    return out_content.str();
  }
  catch (const std::exception& ex)
  {
    GE::Assert(false, ex.what());
    return {};
  }
}
