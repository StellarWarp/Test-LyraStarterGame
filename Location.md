

测试工具被集成在 `Source\LyraGame\Tests\PerformanceTestFunc.h` 中，`FPerformanceTestUtils` 的成员函数均为静态成员，用于增加耗时。详细使用见代码。

通过修改 `FPerformanceTestUtils::enabled` 可启用或禁用所有静态成员函数功能。 

当前源码中有三处高耗时位置分别位于（可通过查找`FPerformanceTestUtils`的引用）
- `ALyraCharacter::OnDeathStarted`：角色死亡时触发
- `ALyraCharacter::PossessedBy`：新创建的角色被控制时触发
- `ULyraCharacterMovementComponent::TickComponent` ：每帧触发

其中 `ULyraCharacterMovementComponent::TickComponent` 为新增函数，其只执行父类行为与高耗时操作