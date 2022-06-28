# OS_Kboard Source Code 구성 및 사용법

---

1. kernel모드의 소스코드는 syscall 처리함수 원형 등록 과정을 수행하지 않았으므로 총 4개입니다.

2. user영역의 소스코드는, syncronize 검증코드 2개가 추가되었습니다. (syncCopy, syncPaste)

3. sync 검증 코드 사용 시에는, ring buffer가 비어있는 상태에서 syncCopy를 먼저 수행하고, syncPaste를 수행해줍니다.

4. os_kboard.c에서 debug message는 주석처리했습니다. 사용 시, 주석을 해제하고 사용하면 됩니다.