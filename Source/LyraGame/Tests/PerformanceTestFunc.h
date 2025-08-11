#pragma once
#include "CoreMinimal.h"
#include "HAL/PlatformProcess.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Subsystems/Subsystem.h"

struct FPerformanceTestUtils
{
	static inline bool enabled = true;

	// @ALyraGameState::Tick 
	static void TickSleep(float DeltaSeconds)
	{
		if (!enabled) return;
		FPlatformProcess::Sleep(DeltaSeconds);
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::TickSleep called with DeltaSeconds: %f"), DeltaSeconds);
	}

	static void TickSleep(void* random_address)
	{
		if (!enabled) return;
		float time = (uint64_t)random_address % 1000 / 10000.0f + 0.05f;
		FPlatformProcess::Sleep(time);
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::TickSleep called with DeltaSeconds: %f"), time);
	}

	static void TickSleepMarked(float DeltaSeconds)
	{
		SCOPED_NAMED_EVENT(PerformanceTestUtils_TickSleep, FColor::Green);
		if (!enabled) return;
		FPlatformProcess::Sleep(DeltaSeconds);
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::TickSleepMarked called with DeltaSeconds: %f"), DeltaSeconds);
	}

	// @ULyraCharacterMovementComponent::TickComponent
	static void FloatCompute(float DeltaSeconds = 0.016f)
	{
		if (!enabled) return;
		float Result = 0.0f;
		for (int i = 0; i < 50000; ++i)
		{
			// Perform some computation
			Result += FMath::Sin(i * DeltaSeconds) * FMath::Cos(i * DeltaSeconds);
			DeltaSeconds -= 0.1f;
		}
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::TickCompute Result: %f"), Result);
	}

	static void FloatComputeMarked()
	{
		SCOPED_NAMED_EVENT(PerformanceTestUtils_TickCompute, FColor::Blue);
		if (!enabled) return;
		float Result = 0.0f;
		float DeltaSeconds = 0.016f;
		for (int i = 0; i < 100000; ++i)
		{
			// Perform some computation
			Result += FMath::Sin(i * DeltaSeconds) * FMath::Cos(i * DeltaSeconds);
			DeltaSeconds -= 0.1f;
		}
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::TickComputeMarked Result: %f"), Result);
	}

	static void ObjectCreation()
	{
		if (!enabled) return;
		TArray<UObject*> CreatedObjects;
		for (int i = 0; i < 1000; ++i)
		{
			UObject* Obj = NewObject<UObject>();
			if (Obj)
			{
				Obj->AddToRoot(); // Prevent garbage collection for this example
				CreatedObjects.Add(Obj);
			}
		}
		//// remove objects from root to allow garbage collection
		for (UObject* Obj : CreatedObjects)
		{
			Obj->RemoveFromRoot();
		}
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::ObjectCreation completed"));
	}

	static void ObjectCreationMarked()
	{
		SCOPED_NAMED_EVENT(PerformanceTestUtils_ObjectCreation, FColor::Yellow);
		if (!enabled) return;
		TArray<UObject*> CreatedObjects;
		for (int i = 0; i < 1000; ++i)
		{
			UObject* Obj = NewObject<UObject>();
			if (Obj)
			{
				Obj->AddToRoot(); // Prevent garbage collection for this example
				CreatedObjects.Add(Obj);
			}
		}
		// remove objects from root to allow garbage collection
		for (UObject* Obj : CreatedObjects)
		{
			Obj->RemoveFromRoot();
		}
		UE_LOG(LogTemp, Log, TEXT("FPerformanceTestUtils::ObjectCreationMarked completed"));
	}
};