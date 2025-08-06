// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Character/LyraCharacter.h"
#include "MyLyraCharacter.generated.h"

/**
 *
 */
UCLASS()
class LYRAGAME_API AMyLyraCharacter : public ALyraCharacter
{
	GENERATED_BODY()

public:
	// ========================================================================
	// MODIFICATION: Added the constructor declaration.
	// This is essential for proper initialization and calling the parent's constructor.
	// ========================================================================
	AMyLyraCharacter(const FObjectInitializer& ObjectInitializer);


public:

	/**
	 * @brief [���ذ汾 2] �������ĺ�ʱ����
	 * C++���Ʊ���Ϊ PerformHeavyTask��
	 */
	UFUNCTION(BlueprintCallable, Category = "MyCharacter|PerformanceTesting", meta = (DisplayName = "Perform Custom Heavy Task"))
	void PerformHeavyTask(int32 Iterations);


	UFUNCTION(BlueprintCallable, Category = "MyCharacter|PerformanceTesting", meta = (DisplayName = "Perform Two Heavy Task"))
	void PerformHeavyTwoTask();
};