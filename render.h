void renderField();
void renderDiceSlots();

const int numberOfSlotRowsPerPlayer = 3;
const int numberOfSlotColsPerPlayer = 3;

//const int numberOfSlotsPerPlayer = numberOfSlotRowsPerPlayer * numberOfSlotColsPerPlayer;
//const int numberOfPlayers = 2;


const float xFieldOrigin{ -0.6f };
const float yFieldOrigin{ 1.0f };

const float fieldLen    { 1.2f };
const float fieldHeight { 2.0f };


const float xSlotOffsetCoeff  { 0.25f }; //const
const float ySlotOffsetCoeff  { 0.25f }; //const

//                   all len *  / ((offset + slot len   )  * num of slots              + last offset    )
const float xOffset{ fieldLen * xSlotOffsetCoeff / ((xSlotOffsetCoeff + 1) * numberOfSlotColsPerPlayer + xSlotOffsetCoeff) };
const float yOffset{ fieldHeight * ySlotOffsetCoeff / ((ySlotOffsetCoeff + 1) * numberOfSlotRowsPerPlayer + ySlotOffsetCoeff)};


const float xSlotOrigin { xFieldOrigin + xOffset};
const float ySlotOrigin { yFieldOrigin - yOffset };

const float slotLen     { xOffset / xSlotOffsetCoeff };
const float slotHeight  { yOffset / ySlotOffsetCoeff };
                    

namespace colors {
    const float windowBackgroundRed   { 96.0f / 256.0f };
    const float windowBackgroundGreen { 98.0f / 256.0f };
    const float windowBackgroundBlue  { 99.0f / 256.0f };
                                      
    const float fieldBackgroundRed    { 0.07f };
    const float fieldBackgroundGreen  { 0.13f };
    const float fieldBackgroundBlue   { 0.17f };

    const float diceSlotRed           { 170.0f / 256.0f };
    const float diceSlotGreen         { 170.0f / 256.0f };
    const float diceSlotBlue          { 170.0f / 256.0f };
}