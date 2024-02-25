<section align="center">

# NezukoCS — A lightweight Garbage Collector for C

![Nezuko's Cleaning Services Banner](nezuko-cleaning-services-banner.png)

</section>

<br>

## _Overview_

NezukoCS is a lightweight **_Garbage Collector_** designed for C programmers to simplify memory management. It provides a set of functions to allocate and deallocate memory efficiently and **_automatically_**, ensuring that memory is properly managed and helping you avoid any **_memory leaks_**.

With **_Nezuko Cleaning Services_** in the house, you can focus on writing clean, reliable code without worrying about memory management complexities.

<br>

## _Features_

- **Allocation and deallocation of memory.**
- **Cleaning up all allocated memory automatically.**

<br>

## _Usage_

NezukoCS provides three main functions for memory management:

- ### Allocate memory

  To allocate memory, use the **_allocate_** function.\
   It takes an _integer_ size of the memory to allocate and returns a _pointer_ to the allocated memory.

  ```c
    int* ptr = allocate(sizeof(int));
  ```

- ### Deallocate memory

  To deallocate memory, use the **_deallocate_** function. It takes a _pointer_ to the memory to deallocate.

  ```c
    deallocate(ptr);
  ```

- ### Clean the heap

  To clean up all allocated memory, just call **_nezuko_** and let her do the rest.

  Nezuko will later update you on the cleaning results at the end of the execution.

  ```c
    nezuko();
  ```

<br>

## _Examples_

- ### Example 1

  ```c
  #include <nezukocs.h>

  int main() {
      // Allocate memory
      int* ptr1 = allocate(sizeof(int));
      double* ptr2 = allocate(sizeof(double) * 10);
      char* ptr3 = allocate(20);

      // Deallocate memory
      deallocate(ptr1);
      deallocate(ptr2);
      deallocate(ptr3);

      return nezuko(); // call Nezuko
  }
  ```

  **Output**

  ```
  It looks like there's nothing left for Nezuko to clean! Good job.
  ```

  <br>

- ### Example 2

  ```c
  #include <nezukocs.h>

  int main() {
      // Allocate memory
      int* ptr1 = allocate(sizeof(int));
      double* ptr2 = allocate(sizeof(double) * 10);
      char* ptr3 = allocate(20);

      // Deallocate ptr1
      deallocate(ptr1);
      deallocate(ptr2);

      // forgot to deallocate ptr3

      return nezuko(); // call Nezuko
  }
  ```

  **Output**

  ```
  Nezuko cleaned 20 bytes of allocated memory.
  ```

  <br>

- ### Example 3

  ```c
  #include <nezukocs.h>

  int main() {
      // Allocate memory
      int* ptr1 = allocate(sizeof(int));
      double* ptr2 = allocate(sizeof(double) * 10);
      char* ptr3 = allocate(20);

      // Didn't deallocate any memory

      return nezuko(); // call Nezuko 😌💗
  }
  ```

  **Output**

  ```
  Nezuko cleaned 104 bytes of allocated memory.
  ```

<br>

## _Installation_

1. **Download the raw file of the code from the github repo:**

   Link: [Download NezukoCS from here](https://fastupload.io/FFxuZehx8oJZyGj/file)

   <br>

2. **Paste the downloaded file in the compiler's _include_ directory:**

   LLVM Clang Compiler: `C:\LLVM\lib\clang\17\include\`

   GNU GCC Compiler: `C:\MinGW\include\`

   **_Note:_** The paths may slightly differ so try to look up your own.

   <br>

3. **Include "nezukoCS.h" in your project:**

   ```c
   #include <nezukoCS.h>
   ```

   <br>
   <br>
   <br>

---

**_Shout out to [Ayres](https://github.com/Ayres-Adel) for all his inspiration, love, and support. 🤍_**
