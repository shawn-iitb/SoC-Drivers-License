# Week 3

So, so, so. You have seen starting form processes to syscalls. You might have the feeling that you know enough already to begin with the actual part of the SOC. One last step before that, before this topic trips people quite a lot. An idea so simple, yet so beautiful and is fundamental to every single running system/phone in this world. An idea which was slid under the carpet in the first week. This is one of those weeks where it sort of all comes together. This week is about Virtual Memory. 

If you already know virtual memory, skip to [here](#oh-you-know-virtual-memory-already)

## But what is Virtual Memory? 

You might've gotten a vague idea of what virtual memory is from the first week. Regardless, it's best to take it slow. 

You might've used arrays quite a lot by now. Have you ever wondered what is the mechanism behind it all, how if you did ```array[3]```, how does your system seamlessly return the value which you put earlier in that place? If you were to implement this, how will you do it? Basically at your hand you have memory of say 1MB and an array that an user asks to store. 

<details>
  <summary style="font-size: 17px;"><b>Think before you open this!</b></summary>

    One of the ways to do it is as simple as it gets. Just allocate it from 0 to 1MB. (Can you figure out how many elements can you store?). So, if I ask for array[3], it is as simple as going to 3 * 4 (assuming integer array) and retrieving 4 bytes from starting from 12.

</details>  
‎

But real programs are not as simple as just accessing an array. But there lies a greater problem at hand. Can you figure out what it is?

<details>
  <summary style="font-size: 17px;"><b>Think before you open this!</b></summary>

    It is very complicated to support multiple programs. Say that you have two programs accessing two arrays. Now in order to access a1 and a2, you have to code in explicitly the addresses that you have access to retrieve the data. But it's very hard to know which addresses will be free at any point. The programmer has to manually hardcode the addresses each time they want to run the program. 
    
    Phew! That's too much to ask from me.

</details>  
‎ 

There lies another problem. Let's say both of our programs are running. Your program(which is not the SOC) takes quite a bit of time and re-running it would be such a pain. I on the other hand have sworn revenge on you for not having done the assignment 2 of the SOC. Is there any way I could sabotage you?

<details>
  <summary style="font-size: 17px;"><b>Think before you open this!</b></summary>

    YES! All I have to know is the address space you are working with and I can do all sort of whacky things there. I can change the state of the data that you're using and whatever you get as an output would be incorrect. This was just an example, but given that there are viruses and other malicious programs out to get you, you get how easy it would be to mess up with your system.

</details>  
   ‎  

There's one more probl... okay, I'll stop. You get the idea now. To get a more formal idea of why this is needed, you can refer to this text to get an introduction to Virtual memory [Chapter 13](http://pages.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf). 


## That's cool, but how on earth do you manage all of this?

At this point if you're wondering: "Okay, if the solution to all of this is just have a address space for everything, how does address translation from this space for each program to physical memory even happen?". Would be a very valid question. 


## Address translation

So, one of the ways you can do it is by <b>"Segmenting"</b> the memory(sounds familiar?). You allocate chunks of memory to each process. But this becomes a headache too as you'll know soon. You can skim through [this](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-segmentation.pdf) and [this](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-mechanism.pdf) if you want to learn more about Segmentation. 

(Unrelated but did you know gdb helps you fix Segmentation faults in a jiffy?)

There's a much more novel, yet simple approach towards memory which is called paging. 

## Paging

The idea is to divide memory into fixed sized chunks and have a map. Refer [Paging](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-paging.pdf) to learn about Paging more.

Quick question: For every single memory access that you make, can you figure out how many times you have to go to memory?

<details>
  <summary style="font-size: 17px;"><b>Think before you open this!</b></summary>

    If its a single level page table, you have to go to memory twice. Recollect that the Page table is also stored in memory(you have to store it somewhere right?), so for every virtual address you ask for, you have to first go to physical memory - get the corresponding physical frame number. Now that you have the physical frame number, congrats! You know exactly where to go in memory to find your precious data. But you still have to go right? This makes it the second access - going and actually fetching the data. So, each memory access demands 2 trips to the memory.

</details>  
   ‎  


But this translation is too slow(even slower when we have multiple levels) and you don't want to be doing this translation for every single memory access that you do. Let's say that you're working with an array which fits in one page. 

<b>Which do think is better: </b>
- Going to memory every single time (OR) 
- Store the transalation which are used quite a lot somewhere

The second option is better because you initially make two accesses, but from there (assuming the translation stays), it will take you just one access. Given that memory accesses take about 100ns compared to a few nanoseconds for retriving the translation, this gives a huge performance boost. This is at the cost of some extra hardware, which is okay at this point.

Read about TLBS under the following links:

[What are TLBs](https://www.techtarget.com/whatis/definition/translation-look-aside-buffer-TLB)

[TLBs in OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf) (You can skip the context switching part)


But the ask for this is too huge. The map in itself takes about roughly 4MB for each program for a 32 bit system! Given that we nowadays have 64 bit systems and you'd have to maintain this for each process, can we do some optimisations maybe?

Yes, Bob. We can. Introducing [Multi-level page tables](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf)


You can refer to this video too: [
Virtual Memory: 12 Multi-level Page Tables](https://www.youtube.com/watch?v=Z4kSOv49GNc)


But, if you don't have the attention span to read a book(me), or just wanna summarize all of what has been put here you can refer to this amazing video:
[But, what is Virtual Memory?](https://www.youtube.com/watch?v=A9WLYbE0p-I)


## Oh, you know Virtual memory already?

Then you can start working on this. Similar to other weeks, this weeks will have an part meant for people new to all of this and a part for people who know all of this already. But if you are new, you are still free to attempt it :)

Going with the theme of memory, writing custom memory managers might come in handy at times and would be a challenge for this week. Check out:

https://developer.ibm.com/tutorials/au-memorymanager/

So, this site has two parts: One basic implementation and one with support for multithreading

You are expected to atleast do the basic implementation. If you feel it to be straightforward however, you can try adding support for multithreading. 

But even if that doesn't challenge you, I know a person... well a link.

https://github.com/HelloWorld017/CS230/tree/master/lab6 

(You can skip the heap consistency checker if you feel it to be too much)

While others are reading and learning about VM, you can get started on your assignment, since it has been a pretty theory heavy not involving a lot of code so far.

Cheers!

## Ending Points

- Feel free to reach out to any of us if you have any difficulty at all in any of these topics. We understand that there is a lot of terms involved, but I strongly suggest to grasp the ideas behind them(which personally I find very simple yet beautiful), and the terms will fall in place later. Don't get frustrated if you can't remember most of them :P
