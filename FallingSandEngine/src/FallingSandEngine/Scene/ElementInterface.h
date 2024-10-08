#pragma once
// i dont know if this is good
#include <glm/glm.hpp>
#include "Components.h"
namespace FallingSandEngine
{
	class ElementInterface
	{
	public:
		virtual ~ElementInterface() = default;
		virtual uint8_t GetDensity() const = 0;
		virtual uint8_t GetStackingFactor() const = 0;
		virtual uint8_t GetFriction() const = 0;
		virtual glm::vec4 GetColor() const = 0;
		virtual void TryAwake(int x, int y, ChunkComponent& chunk) = 0;
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) = 0;
		virtual float GetStability(int x, int y, ChunkComponent& chunk) = 0;

		static ElementType GetElementType(CellData cellData)
		{

			return static_cast<ElementType>(cellData & ELEMENT_TYPE_MASK);
		}

		static void SetElementType(uint64_t& cellData, ElementType type)
		{
			cellData = (cellData & ~ELEMENT_TYPE_MASK) | static_cast<uint64_t>(type);
		}

		static bool GetFlag(CellData cellData, uint8_t flag)
		{
			return (cellData & (1ull << (ELEMENT_FLAGS_SHIFT + flag))) != 0;
		}

		static void SetFlag(CellData& cellData, uint8_t flag, bool value)
		{
			if (flag >= 8) // Ensure flag is within valid range (0-7 based on 8 bits)
			{
				// Handle invalid flag case
				FSE_CORE_ERROR("Flag out of bounds: {0}", flag);
				return;
			}

			uint64_t flagShift = (1ull << (ELEMENT_FLAGS_SHIFT + flag)) & ELEMENT_FLAGS_MASK;

			if (value)
				cellData |= flagShift; // Set flag
			else
				cellData &= ~flagShift; // Clear flag
		}

		// Get and Set Velocity Functions
		static int8_t GetVelocityX(CellData cellData)
		{
			return DecodeVelocity((cellData & ELEMENT_VELOCITY_X_MASK) >> ELEMENT_VELOCITY_X_SHIFT);
		}

		static void SetVelocityX(CellData& cellData, int8_t velocity)
		{
			uint8_t encodedVelocity = EncodeVelocity(velocity);

			// Clear the X velocity bits by applying the inverse of the mask
			//FSE_CORE_INFO("SetVelocityX - Raw CellData before masking and clearing X velocity bits: {0:X}", cellData);
			cellData &= ~ELEMENT_VELOCITY_X_MASK;
			//FSE_CORE_INFO("SetVelocityX - Raw CellData after clearing X velocity bits: {0:X}", cellData);

			// Set the new encoded velocity, making sure the shift aligns properly with the mask
			cellData |= (static_cast<CellData>(encodedVelocity) << ELEMENT_VELOCITY_X_SHIFT) & ELEMENT_VELOCITY_X_MASK;
			//FSE_CORE_INFO("SetVelocityX - Raw CellData after setting X velocity: {0:X}", cellData);
		}

		static int8_t GetVelocityY(CellData cellData)
		{
			
			return DecodeVelocity((cellData & ELEMENT_VELOCITY_Y_MASK) >> ELEMENT_VELOCITY_Y_SHIFT);
		}

		static void SetVelocityY(CellData& cellData, int8_t velocity)
		{
			uint8_t encodedVelocity = EncodeVelocity(velocity);

			// Clear the Y velocity bits by applying the inverse of the mask
			//FSE_CORE_INFO("SetVelocityY - Raw CellData before masking and clearing Y velocity bits: {0:X}", cellData);
			cellData &= ~ELEMENT_VELOCITY_Y_MASK;
			//FSE_CORE_INFO("SetVelocityY - Raw CellData after clearing Y velocity bits: {0:X}", cellData);

			// Set the new encoded velocity, ensuring correct alignment
			cellData |= (static_cast<CellData>(encodedVelocity) << ELEMENT_VELOCITY_Y_SHIFT) & ELEMENT_VELOCITY_Y_MASK;
			//FSE_CORE_INFO("SetVelocityY - Raw CellData after setting Y velocity: {0:X}", cellData);
		}

		static void AddVelocityY(CellData& cellData, int8_t delta)
		{
			int8_t currentVelocity = GetVelocityY(cellData);
			//FSE_CORE_INFO("Velocity current: {0}", currentVelocity);
			int8_t newVelocity = glm::clamp(currentVelocity + delta, -32, 31);
			SetVelocityY(cellData, newVelocity);
		}

		static void AddVelocityX(CellData& cellData, int8_t delta)
		{
			int8_t currentVelocity = GetVelocityX(cellData);
			int8_t newVelocity = glm::clamp(currentVelocity + delta, -32, 31);
			SetVelocityX(cellData, newVelocity);
		}
	private:
		static const CellData ELEMENT_TYPE_MASK = 0x000000000000FFFFULL; // 16 bits
		static const uint8_t ELEMENT_FLAGS_SHIFT = 16; // 8 bits for flags starting at bit 16
		static const CellData ELEMENT_FLAGS_MASK = 0x0000000000FF0000ULL;

		static const uint8_t ELEMENT_VELOCITY_X_SHIFT = 24;       // X velocity starts at bit 24
		static const uint8_t ELEMENT_VELOCITY_Y_SHIFT = 30;       // Y velocity starts at bit 30
		static const CellData ELEMENT_VELOCITY_X_MASK = 0x000000003F000000ULL; // 6 bits for X velocity
		static const CellData ELEMENT_VELOCITY_Y_MASK = 0x0000000FC0000000ULL; // 6 bits for Y velocity

		static uint8_t EncodeVelocity(int8_t velocity)
		{
			int8_t encoded = static_cast<uint8_t>(velocity + 32);
			//FSE_CORE_INFO("Ecoding velocity: Raw = {0}, Encoded = {1}", velocity, encoded);
			return encoded;
		}

		// Helper to decode velocity (map from 0 to 63 to -32 to +31)
		static int8_t DecodeVelocity(uint8_t encodedVelocity)
		{
			int8_t decoded = static_cast<int8_t>(encodedVelocity - 32);
			//FSE_CORE_INFO("Decoding velocity: Encoded = {0}, Decoded = {1}", encodedVelocity, decoded);
			return decoded;
		}

	public:
		enum FlagPositions
		{
			UPDATED_FLAG,
			AWAKE_FLAG,
			UNUSED2,
			UNUSED3,
			UNUSED4,
			UNUSED5,
			UNUSED6,
			UNUSED7
		};
	};
}