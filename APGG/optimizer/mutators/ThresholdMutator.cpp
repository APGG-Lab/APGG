#include "ThresholdMutator.h"

void APGG::ThresholdMutator::setThreshold(const float threshold)
{
    m_threshold = threshold;
}

void APGG::ThresholdMutator::mutate(const std::vector<rOrganism>& selection)
{
    for (rOrganism org : selection)
    {
        if (m_motationRate < getRandomFloat()) {
            continue;
        }

        for (int i = 0; i < org.get().m_genomes.size(); i++) {
            float randomFloat = getRandomFloat();

            float genomeBaseValue = org.get().m_genomes[i].getValue();

            //base - thres   <=   randomFloat   <= base + thres
            //genomeMinValue <=   randomFloat   <= genomeMaxValue
            if (genomeBaseValue - m_threshold >= randomFloat && genomeBaseValue + m_threshold <= randomFloat) {
                org.get().m_genomes[i].setValue(randomFloat);
                org.get().m_mutated = true;
            }
        }
    }
}
