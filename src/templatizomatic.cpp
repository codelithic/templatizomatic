
#include "templatizomatic/templatizomatic.hpp"

#include <dirent.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace kainjow::mustache;

namespace templatizomatic {

const std::string& Tpl::getTemplate() const { return Tpl::sTemplate; }

void Templatizomatic::dump() {}

const templatizomatic::Tpl* Templatizomatic::getTemplete(
    const std::string& name) {
  auto tpl = tpls.find(name);
  if (tpl != tpls.end()) {
    return tpl->second.get();
  }
  return nullptr;
}

void Templatizomatic::init(void* params) {}

void Templatizomatic::fillSiteData(templatizomatic::Data& data) {
  for (auto& d : this->siteData) {
    data.set(d.first, d.second);
  }
}

void Templatizomatic::addSiteData(std::string_view name,
                                  std::string_view data) {
  siteData.insert(std::pair<std::string, std::string>(name, data));
}

void Templatizomatic::myreplace(std::string& str, const std::string& from,
                                const std::string& to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

void Templatizomatic::addTemplate(const std::string& key,
                                  const std::string& content) {
  tpls[key] = std::make_unique<Tpl>(content);
}

void Templatizomatic::loadFile(const std::string& filePath,
                               std::string& buffer) {
  std::ifstream t(filePath);
  std::stringstream sBuffer;
  sBuffer << t.rdbuf();
  buffer.assign(sBuffer.str());
}

void Templatizomatic::loadTemplates(const std::string& tPath) {
  if (!tPath.empty()) {
    std::string base;
    DIR* d;
    struct dirent* dir;
    d = opendir(tPath.data());
    if (d) {
      std::string filePath;
      std::string fileContent;
      while ((dir = readdir(d)) != nullptr) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
        } else {
          filePath.assign(dir->d_name);
          if (filePath.find(".lsd") != std::string::npos) {
            base = tPath;
            base.append("/").append(dir->d_name);
            // T2LOGGER_DEBUG(logger,dir->d_name);
            loadFile(base, fileContent);

            addTemplate(filePath, fileContent);
          }
        }
      }
    }
    closedir(d);
  }
}

}  // namespace templatizomatic
