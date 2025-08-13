
# 测试文档

测试工具被集成在 `Source\LyraGame\Tests\PerformanceTestFunc.h` 中的 `FPerformanceTestUtils`， 其的成员函数均为静态成员，用于增加耗时。详细使用见代码。

通过修改 `FPerformanceTestUtils::enabled` 可启用或禁用所有测试点。 

# 测试实例 \# `commit 4e90b0b`

当前源码中有三处高耗时位置分别位于
- `ALyraCharacter::OnDeathStarted`：角色死亡时触发
    ``` cpp
    void ALyraCharacter::OnDeathStarted(AActor*)
    {
        DisableMovementAndCollision();
        FPerformanceTestUtils::TickSleep(0.03);
    }
    ```
- `ALyraCharacter::PossessedBy`：新创建的角色被控制时触发
  ```cpp
    void ALyraCharacter::PossessedBy(AController* NewController)
    {
        const FGenericTeamId OldTeamID = MyTeamID;

        Super::PossessedBy(NewController);

        ...

        FPerformanceTestUtils::TickSleep(0.02);
    }
  ```
- `ULyraCharacterMovementComponent::TickComponent` ：每帧触发
    ```cpp
    void ULyraCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
    {
        Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
        FPerformanceTestUtils::FloatCompute(DeltaTime);
    }
    ```

---
## Profile \# `20250811_132317.utrace`

当前三个测试点均为高耗时操作，在 Profile 中有明显特征。

### 测试点 1&2

位于 `ALyraCharacter::OnDeathStarted` 与 `ALyraCharacter::PossessedBy` 的测试点会引起**单帧耗时增加**。

- 由 `ALyraCharacter::OnDeathStarted` 测试点引起，如 `Rendering Frame 270` `Rendering Frame 818` `Rendering Frame 1072`
- `ALyraCharacter::PossessedBy` 测试点引起，如
`Rendering Frame 466` `Rendering Frame 1019`

出现**超出预算的高耗时的叶子节点**，如 
- `OnDeathStarted (88.2 ms)` 
- `B_AI_Controller_LyraShooter_C (244.1 ms)` 
- `LyraPlayerController (288 ms)`

### 测试点 3

`ULyraCharacterMovementComponent::TickComponent` 测试点每帧触发，将导致 Actor Tick 耗时增加。表现为每个 Actor 中 `FActorComponentTickFunction::ExecuteTick`显著增加。其中出现**高占比的未标注区间**，此将大幅降低平均FPS。