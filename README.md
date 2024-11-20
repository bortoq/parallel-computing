# parallel-computing
/*
* TO DESCRIBE THE DEVICE OF PARALLEL ADDRESSABLE COPIES AND THEIR USE
* TO PERFORM SCALAR-VECTOR CALCULATIONS
*
* copyright 2019-2024, dmitri bortoq
*/

  Any Turing computation can be reduced to two-place Boolean functions. any function can be represented by a table of its values and computed by addressable copies from the table (look up table). addressing can be performed by a sorting mechanism.
  addressing is performed due to what any sorting provides: wherever an index is located, it will take its position after sorting is completed. if position indices with a data bit and a copying direction bit attached to them are used as sorted values, it will be enough to construct a copy of an absolutely addressable value.
  parallel copying is possible due to correct operation of data oblivious sorting that calculates addressing. addressing is performed correctly if the addresses used in copying are unique. address uniqueness is ensured by consistency of copying. consistency is ensured by the virtual part of the mechanism.
  while addressing setup by instructions and index sorting are performed, the calculation cycles consisting of parallel copies of bit strings will also be performed. the setup cycle and the sorting cycle can be performed pipelined. the device performing these actions (space emulator) consists of two parts. the first part is minimal and is necessary to ensure the operability of the second part - virtual part of the mechanism.
 

/*
 * ОПИСАНИЕ УСТРОЙСТВА ПАРАЛЛЕЛЬНЫХ АДРЕСУЕМЫХ КОПИРОВАНИЙ И ИХ ИСПОЛЬЗОВАНИЯ
 * ДЛЯ ПРОВЕДЕНИЯ СКАЛЯРНО-ВЕКТОРНЫХ ВЫЧИСЛЕНИЙ
 *
 * copyright 2019-2024, dmitri bortoq
 */

  любое вычисление по тьюрингу можно свести к двухместным булевым функциям. любую функцию можно представить таблицей ее значений и вычислять адресуемыми копированиями из таблицы (look up table). адресацию можно выполнить механизмом сортировки.
  адресация проводится за счет того, что обеспечивает любая сортировка: где бы ни находился индекс он займет свою позицию после окончания сортировки. если в качестве сортируемых значений использовать индексы позиций с прикрепленными к ним битом данных и битом направления копирования, то этого будет достаточно для построения копирования адресуемого абсолютно.
  параллельные копирования возможны благодаря корректной работе data oblivious sorting вычисляющей адресацию. адресация выполняется корректно если используемые при копировании адреса уникальны. уникальность адресов обеспечивается согласованностью копирований. согласованность обеспечивается виртуальной частью механизма.
  пока будет выполняться настройка адресации инструкциями и сортировка индексов, будут выполняться и такты вычисления, состоящего из параллельных копирований битовых строк. такт настройки и такт сортировки могут быть выполнены конвейерно. устройство выполняющее эти действия (эмулятор пространства) состоит из двух частей. первая часть является минимальной и нужна для обеспечения работоспособности второй - виртуальной, расположенной в пространстве создаваемой первой частью. поэтому обработка ввода-вывода, обеспечение согласованности, биллинг и все остальные функции механизма отсутствуют в коде эмулятора.
