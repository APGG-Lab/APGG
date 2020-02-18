#include "MatchupGenerator.h"

namespace APGG {
    void MatchupGenerator::configure(Config& config)
    {
        setGroupSize(stoul(config.getValue("groupSize", "10")));
    }

    void MatchupGenerator::setGroupSize(const unsigned int size)
    {
        m_groupSize = size;
    }
    std::vector<Group>& MatchupGenerator::getGroups()
    {
        return m_groups;
    }
  //  std::vector<Group> MatchupGenerator::getGroups() const
 //   {
  //      return m_groups;
  //  }
}