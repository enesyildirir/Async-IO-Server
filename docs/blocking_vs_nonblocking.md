# Blocking ve Non-Blocking I/O

*Kisi 1 tarafından yazılmıştır — REPORT.md'nin teknik altyapısıdır.*

## Blocking I/O

`recv()` çağrıldığında veri gelene kadar thread **durur**, başka hiçbir şey yapamaz.

```c
int n = recv(sockfd, buf, sizeof(buf), 0);
/* ↑ veri gelene kadar burası bekler */
```

Her istemci için ayrı thread gerekir → 100 istemci = 100 thread = yüksek bellek.

## Non-Blocking I/O

Soket `O_NONBLOCK` ile açılır. `recv()` hemen döner:
- Veri varsa okur
- Veri yoksa `errno = EAGAIN` döner (hata değil)

```c
fcntl(sockfd, F_SETFL, O_NONBLOCK);
int n = recv(sockfd, buf, sizeof(buf), 0);
if (n < 0 && errno == EAGAIN) { /* veri yok, devam */ }
```

Tek thread yüzlerce soketi yönetebilir.

## epoll

"Hangi sokette veri var?" sorusunu O(aktif event) ile cevaplar.
select/poll O(n) tarar — epoll sadece hazır olanları döndürür.

| | select | poll | epoll |
|--|--------|------|-------|
| Max fd | ~1024 | Sınırsız | Sınırsız |
| Maliyet | O(n) | O(n) | O(hazır) |
| Platform | POSIX | POSIX | Linux |
