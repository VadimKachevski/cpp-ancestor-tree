#include "doctest.h"
#include <iostream>
#include "FamilyTree.hpp"

using namespace family;

TEST_CASE("First tree")
{
    family::Tree T("Yosef");          // Yosef is the "root" of the tree (the youngest person).
    T.addFather("Yosef", "Yaakov")    // Tells the tree that the father of Yosef is Yaakov.
        .addMother("Yosef", "Rachel") // Tells the tree that the mother of Yosef is Rachel.
        .addFather("Yaakov", "Isaac")
        .addMother("Yaakov", "Rivka")
        .addFather("Isaac", "Avraham")
        .addFather("Avraham", "Terah")
        .addFather("Rachel", "david")
        .addMother("Rachel", "RachelsMother")
        .addMother("david", "davidMother")
        .addFather("david", "davidFather")
        .addFather("RachelsMother", "RachelsMotherFather")
        .addMother("RachelsMother", "RachelsMotherMother")
        .addMother("RachelsMotherMother", "RachelsMotherMotherMother")
        .addFather("RachelsMotherMother", "RachelsMotherMotherFather")
        .addMother("RachelsMotherMotherFather", "uhhMother")
        .addMother("uhhMother", "GoingToMotherTrip")
        .addMother("GoingToMotherTrip", "mother")
        .addMother("mother", "finalMother");

    CHECK(T.relation("Yaakov").compare("father") == 0);
    CHECK(T.relation("Rachel").compare("mother") == 0);
    CHECK(T.relation("Rivka").compare("grandmother") == 0);
    CHECK(T.relation("Isaac").compare("grandfather") == 0);
    CHECK(T.relation("david").compare("grandfather") == 0);
    CHECK(T.relation("RachelsMother").compare("grandmother") == 0);
    CHECK(T.relation("Avraham").compare("great-grandfather") == 0);
    CHECK(T.relation("Terah").compare("great-great-grandfather") == 0);
    CHECK(T.relation("davidMother").compare("great-grandmother") == 0);
    CHECK(T.relation("davidFather").compare("great-grandfather") == 0);
    CHECK(T.relation("RachelsMotherFather").compare("great-grandfather") == 0);
    CHECK(T.relation("RachelsMotherMother").compare("great-grandmother") == 0);
    CHECK(T.relation("RachelsMotherMotherMother").compare("great-great-grandmother") == 0);
    CHECK(T.relation("RachelsMotherMotherFather").compare("great-great-grandfather") == 0);
    CHECK(T.relation("uhhMother").compare("great-great-great-grandmother") == 0);
    CHECK(T.relation("GoingToMotherTrip").compare("great-great-great-great-grandmother") == 0);
    CHECK(T.relation("mother").compare("great-great-great-great-great-grandmother") == 0);
    CHECK(T.relation("finalMother").compare("great-great-great-great-great-great-grandmother") == 0);
    CHECK(T.find("father").compare("Yaakov") == 0);
    CHECK(T.find("mother").compare("Rachel") == 0);
    CHECK(T.find("grandmother").compare("Rivka") == 0);
    CHECK(T.find("grandfather").compare("Isaac") == 0);
    CHECK(T.find("great-grandfather").compare("Avraham") == 0);
    CHECK(T.find("great-grandmother").compare("davidMother") == 0);
    CHECK(T.find("great-great-grandmother").compare("RachelsMotherMotherMother") == 0);
    CHECK(T.find("great-great-grandfather").compare("Terah") == 0);
    CHECK(T.find("great-great-great-grandmother").compare("uhhMother") == 0);
    CHECK(T.find("great-great-great-great-grandmother").compare("GoingToMotherTrip") == 0);
    CHECK(T.find("great-great-great-great-great-grandmother").compare("mother") == 0);
    CHECK(T.find("great-great-great-great-great-great-grandmother").compare("finalMother") == 0);
    T.remove("finalMother");
    CHECK(T.relation("finalMother").compare("unrelated") == 0);
    T.remove("mother");
    CHECK(T.relation("mother").compare("unrelated") == 0);
    T.remove("GoingToMotherTrip");
    CHECK(T.relation("GoingToMotherTrip").compare("unrelated") == 0);
    T.remove("uhhMother");
    CHECK(T.relation("uhhMother").compare("unrelated") == 0);
    T.remove("Terah");
    CHECK(T.relation("Terah").compare("unrelated") == 0);
    T.remove("RachelsMotherMotherMother");
    CHECK(T.relation("RachelsMotherMotherMother").compare("unrelated") == 0);
    T.remove("davidMother");
    CHECK(T.relation("davidMother").compare("unrelated") == 0);
    T.remove("Avraham");
    CHECK(T.relation("Avraham").compare("unrelated") == 0);
    T.remove("Isaac");
    CHECK(T.relation("Isaac").compare("unrelated") == 0);
    T.remove("Rivka");
    CHECK(T.relation("Rivka").compare("unrelated") == 0);
    T.remove("Rachel");
    CHECK(T.relation("Rachel").compare("unrelated") == 0);
    T.remove("Yaakov");
    CHECK(T.relation("Yaakov").compare("unrelated") == 0);

    T.addFather("Yosef", "Yaakov")    // Tells the tree that the father of Yosef is Yaakov.
        .addMother("Yosef", "Rachel") // Tells the tree that the mother of Yosef is Rachel.
        .addFather("Yaakov", "Isaac")
        .addMother("Yaakov", "Rivka")
        .addFather("Isaac", "Avraham")
        .addFather("Avraham", "Terah")
        .addFather("Rachel", "david")
        .addMother("Rachel", "RachelsMother")
        .addMother("david", "davidMother")
        .addFather("david", "davidFather")
        .addFather("RachelsMother", "RachelsMotherFather")
        .addMother("RachelsMother", "RachelsMotherMother")
        .addMother("RachelsMotherMother", "RachelsMotherMotherMother")
        .addFather("RachelsMotherMother", "RachelsMotherMotherFather")
        .addMother("RachelsMotherMotherFather", "uhhMother")
        .addMother("uhhMother", "GoingToMotherTrip")
        .addMother("GoingToMotherTrip", "mother")
        .addMother("mother", "finalMother");

    T.remove("Rachel");
    T.remove("Yaakov");
    CHECK(T.relation("finalMother").compare("unrelated") == 0);
    CHECK(T.relation("mother").compare("unrelated") == 0);
    CHECK(T.relation("GoingToMotherTrip").compare("unrelated") == 0);
    CHECK(T.relation("uhhMother").compare("unrelated") == 0);
    CHECK(T.relation("Terah").compare("unrelated") == 0);
    CHECK(T.relation("RachelsMotherMotherMother").compare("unrelated") == 0);
    CHECK(T.relation("davidMother").compare("unrelated") == 0);
    CHECK(T.relation("Avraham").compare("unrelated") == 0);
    CHECK(T.relation("Isaac").compare("unrelated") == 0);
    CHECK(T.relation("Rivka").compare("unrelated") == 0);
    CHECK(T.relation("Rachel").compare("unrelated") == 0);
    CHECK(T.relation("Yaakov").compare("unrelated") == 0);
}
TEST_CASE("Second Tree")
{
    family::Tree T("1");
    T.addFather("1","2")
    .addMother("1","3")
    .addFather("2","4")
    .addMother("2","5")
    .addFather("3","6")
    .addMother("3","7")
    .addFather("4","8")
    .addMother("4","9")
    .addFather("5","10")
    .addMother("5","11")
    .addFather("6","12")
    .addMother("6","13")
    .addFather("7","14")
    .addMother("7","15")
    .addFather("8","16")
    .addMother("8","17")
    .addFather("9","18")
    .addMother("10","19")
    .addFather("11","20")
    .addMother("12","21");



    CHECK(T.relation("2").compare("father") == 0);
    CHECK(T.relation("3").compare("mother") == 0);
    CHECK(T.relation("4").compare("grandfather") == 0);
    CHECK(T.relation("5").compare("grandmother") == 0);
    CHECK(T.relation("6").compare("grandfather") == 0);
    CHECK(T.relation("7").compare("grandmother") == 0);
    CHECK(T.relation("8").compare("great-grandfather") == 0);
    CHECK(T.relation("9").compare("great-grandmother") == 0);
    CHECK(T.relation("10").compare("great-grandfather") == 0);
    CHECK(T.relation("11").compare("great-grandmother") == 0);
    CHECK(T.relation("12").compare("great-grandfather") == 0);
    CHECK(T.relation("13").compare("great-grandmother") == 0);
    CHECK(T.relation("14").compare("great-grandfather") == 0);
    CHECK(T.relation("15").compare("great-grandmother") == 0);
    CHECK(T.relation("16").compare("great-great-grandfather") == 0);
    CHECK(T.relation("17").compare("great-great-grandmother") == 0);
    CHECK(T.relation("18").compare("great-great-grandfather") == 0);
    CHECK(T.relation("19").compare("great-great-grandmother") == 0);
    CHECK(T.relation("20").compare("great-great-grandfather") == 0);
    CHECK(T.relation("21").compare("great-great-grandmother") == 0);

    CHECK(T.find("father").compare("2") == 0);
    CHECK(T.find("mother").compare("3") == 0);
    CHECK(T.find("grandmother").compare("5") == 0);
    CHECK(T.find("grandfather").compare("4") == 0);
    CHECK(T.find("great-grandfather").compare("8") == 0);
    CHECK(T.find("great-grandmother").compare("9") == 0);
    CHECK(T.find("great-great-grandmother").compare("17") == 0);
    CHECK(T.find("great-great-grandfather").compare("16") == 0);

    T.remove("21");
    CHECK(T.relation("21").compare("unrelated") == 0);
    T.remove("20");
    CHECK(T.relation("20").compare("unrelated") == 0);
    T.remove("19");
    CHECK(T.relation("19").compare("unrelated") == 0);
    T.remove("18");
    CHECK(T.relation("18").compare("unrelated") == 0);
    T.remove("17");
    CHECK(T.relation("17").compare("unrelated") == 0);
    T.remove("16");
    CHECK(T.relation("16").compare("unrelated") == 0);
    T.remove("15");
    CHECK(T.relation("15").compare("unrelated") == 0);
    T.remove("14");
    CHECK(T.relation("14").compare("unrelated") == 0);
    T.remove("13");
    CHECK(T.relation("13").compare("unrelated") == 0);
    T.remove("12");
    CHECK(T.relation("12").compare("unrelated") == 0);
    T.remove("11");
    CHECK(T.relation("11").compare("unrelated") == 0);
    T.remove("10");
    CHECK(T.relation("10").compare("unrelated") == 0);
    T.remove("9");
    CHECK(T.relation("9").compare("unrelated") == 0);
    T.remove("8");
    CHECK(T.relation("8").compare("unrelated") == 0);
    T.remove("7");
    CHECK(T.relation("7").compare("unrelated") == 0);
    T.remove("6");
    CHECK(T.relation("6").compare("unrelated") == 0);
    T.remove("5");
    CHECK(T.relation("5").compare("unrelated") == 0);
    T.remove("4");
    CHECK(T.relation("4").compare("unrelated") == 0);
    T.remove("3");
    CHECK(T.relation("3").compare("unrelated") == 0);
    T.remove("2");
    CHECK(T.relation("2").compare("unrelated") == 0);


}