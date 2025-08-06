// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLyraCharacter.h"
#include "ProfilingDebugging/CpuProfilerTrace.h"


AMyLyraCharacter::AMyLyraCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// You can add any initialization logic specific to AMyLyraCharacter here.
	// For now, we leave it empty to ensure no logic is changed,
	// just faithfully passing control to the parent.
}

// ���еĴ������汾��ʵ�֣�����Ķ���
void AMyLyraCharacter::PerformHeavyTask(int32 Iterations)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AMyLyraCharacter::PerformHeavyTask);

	UE_LOG(LogTemp, Warning, TEXT("C++ Heavy Task: Starting... Iterations: %s"), *FString::FormatAsNumber(Iterations));

	const double StartTime = FPlatformTime::Seconds();

	for (int32 i = 0; i < Iterations; ++i)
	{
		volatile float DummyCalculation = FMath::Sin(static_cast<float>(i)) * FMath::Cos(static_cast<float>(i));
	}

	const double EndTime = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("C++ Heavy Task: Finished. Duration: %f seconds"), EndTime - StartTime);
}


// ���еĴ������汾��ʵ�֣�����Ķ���
void AMyLyraCharacter::PerformHeavyTwoTask()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AMyLyraCharacter::PerformHeavyTwoTask);

	for (int i = 0; i < 2; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("start heavyTask loop"));
		this->PerformHeavyTask(1000000); // �������еĴ������汾
	}

	UE_LOG(LogTemp, Warning, TEXT("start heavyTask 1"));
	this->PerformHeavyTask(1000000); // �������еĴ������汾


	UE_LOG(LogTemp, Warning, TEXT("start heavyTask 2"));
	this->PerformHeavyTask(1000000); // �������еĴ������汾
}
