package stackAndQueue

import java.lang.RuntimeException

open class Pet(var name: String) {
}

class Cat(name: String) : Pet(name = name) {

}

class Dog(name: String) : Pet(name = name) {

}

class PetAndCatQueue {
    class CatWithIndex(var cat: Cat, var index: Int) {}
    class DogWithIndex(var dog: Dog, var index: Int) {}

    var cats = ArrayDeque<CatWithIndex>()
    var dogs = ArrayDeque<DogWithIndex>()
    var index = 0

    fun addCat(cat: Cat) {
        this.cats.add(CatWithIndex(cat, index++))
    }

    fun addDog(dog: Dog) {
        this.dogs.add(DogWithIndex(dog, index++))
    }

    fun addPet(pet: Pet) {
        when (pet) {
            is Cat -> {
                this.cats.add(CatWithIndex(pet, index++))
            }
            is Dog -> {
                this.dogs.add(DogWithIndex(pet, index++))
            }
            else -> {
                throw Exception("unrecognized pet")
            }
        }
    }

    fun popCat(): Cat {
        if (this.cats.isEmpty()) {
            throw RuntimeException("There's no cat in the queue")
        }
        return this.cats.removeFirst().cat
    }

    fun popDog(): Dog {
        if (this.dogs.isEmpty()) {
            throw RuntimeException("There's no dog in the queue")
        }
        return this.dogs.removeFirst().dog
    }

    fun popAll(): Pet {
        if (this.cats.isEmpty() && this.dogs.isEmpty()) {
            throw RuntimeException("There's no pet in the queue")
        }
        if (this.cats.isEmpty()) {
            return this.dogs.removeFirst().dog
        }
        if (this.dogs.isEmpty()) {
            return this.cats.removeFirst().cat
        }

        val catIndex = this.cats.first().index
        val dogIndex = this.dogs.first().index

        return if (catIndex < dogIndex) {
            this.cats.removeFirst().cat
        } else {
            this.dogs.removeFirst().dog
        }
    }
}

fun main() {
    val queue = PetAndCatQueue()
    val cat1 = Cat("cat1")
    val cat2 = Cat("cat2")
    val dog3 = Dog("dog3")
    val cat4 = Cat("cat4")
    val dog5 = Dog("dog5")

    queue.addCat(cat1)
    queue.addPet(cat2)
    queue.addDog(dog3)
    queue.addPet(cat4)
    queue.addPet(dog5)

    println("1 pet:${queue.popAll().name}")
    println("2 pet:${queue.popAll().name}")
    println("3 pet:${queue.popAll().name}")
    println("4 pet:${queue.popAll().name}")
    println("5 pet:${queue.popAll().name}")

}
