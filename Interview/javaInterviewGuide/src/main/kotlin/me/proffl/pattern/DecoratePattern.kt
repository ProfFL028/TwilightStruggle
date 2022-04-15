package me.proffl.pattern

interface IDecorate {
    fun show()
}

open class Person(var name: String = "") : IDecorate {
    override fun show() {
        println(name)
    }
}

open class Finery(var person: Person? = null) : Person() {
    fun decorate(person: Person) {
        this.person = person
    }
    override fun show() {
        person?.show()
    }
}

class TShirt : Finery() {
    override fun show() {
        super.show()
        println("T-shirts")
    }
}

class BigTrouser: Finery() {
    override fun show() {
        super.show()
        println("Big trouser")
    }
}

class Sneakers: Finery() {
    override fun show() {
        super.show()
        println("Sneakers")
    }
}

class LeatherShoes: Finery() {
    override fun show() {
        super.show()
        println("Leather Shoes")
    }
}

class Tie: Finery() {
    override fun show() {
        super.show()
        println("Tie")
    }
}

class Suit: Finery() {
    override fun show() {
        super.show()
        println("Suit")
    }
}

fun main() {
    val person = Person("person 1")
    val sneakers = Sneakers()
    val bigTrouser = BigTrouser()
    val tShirt = TShirt()
    val leatherShoes = LeatherShoes()
    val tie = Tie()
    var suit = Suit()

    sneakers.decorate(person)
    bigTrouser.decorate(sneakers)
    tShirt.decorate(bigTrouser)
    tShirt.show()

    val person2 = Person("person 2")
    leatherShoes.decorate(person2)
    tie.decorate(leatherShoes)
    suit.decorate(tie)
    suit.show()
}