# OS_Kboard Source Code ���� �� ����

---

1. kernel����� �ҽ��ڵ�� syscall ó���Լ� ���� ��� ������ �������� �ʾ����Ƿ� �� 4���Դϴ�.

2. user������ �ҽ��ڵ��, syncronize �����ڵ� 2���� �߰��Ǿ����ϴ�. (syncCopy, syncPaste)

3. sync ���� �ڵ� ��� �ÿ���, ring buffer�� ����ִ� ���¿��� syncCopy�� ���� �����ϰ�, syncPaste�� �������ݴϴ�.

4. os_kboard.c���� debug message�� �ּ�ó���߽��ϴ�. ��� ��, �ּ��� �����ϰ� ����ϸ� �˴ϴ�.