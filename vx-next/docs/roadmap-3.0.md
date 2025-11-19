# Teleport VX Next 3.0 — Roadmap

## Этап 1. Поднять ядро в QEMU
1. Создать отдельный Makefile для vx-next (не трогая старый Teleport VX 2.x).
2. Добавить сборку:
   - task.c, task.h
   - scheduler.c
   - kernel.c
   - space.c, space.h
   - capability.c, capability.h
3. Написать минимальный boot.asm + multiboot header.
4. Собрать ISO и загрузить в QEMU.
5. Убедиться, что вызывается vx_kernel_main() и система не падает.

## Этап 2. Реальный планировщик и задачи
1. Реализовать task_create():
   - выделение стека,
   - начальный контекст (eip = entry).
2. Создать 2–3 тестовые задачи:
   - мигающий вывод текста,
   - счётчик тиков.
3. В основном цикле ядра вызывать scheduler_run().

## Этап 3. Spaces
1. Реализовать space_create(), space_get(), space_destroy().
2. Привязать задачи к space_id.
3. Сделать system-space и user-space.
4. Добавить отдельный сервис vx-space (в директории services/).

## Этап 4. Capability безопаность
1. Прописать capabilities у system-space и user-space.
2. Перед доступом к FS/NET/DEVICE проверять cap_check().
3. Добавить базовый лог отказов доступа.

## Этап 5. Сервисы
1. vx-term — терминал/консоль.
2. vx-fs — файловая система (RAMFS/FAT).
3. vx-net — сеть (позже).
4. vx-ai — сервис телеметрии и анализа.

## Этап 6. UX и Neon-интерфейс
1. Загрузочный экран Teleport VX Next.
2. Графический режим (VESA/FrameBuffer).
3. Neon UI поверх системных сервисов.

---

**Текущее состояние (по коду):**
- [x] task.h / task.c — структуры задач и каркас API
- [x] scheduler.c — каркас round-robin
- [x] kernel.c — vx_kernel_main()
- [x] space.h / space.c — структуры пространств
- [x] capability.h / capability.c — модель capabilities
- [x] design-space.md, design-kernel-core.md — архитектура