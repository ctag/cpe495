document.addEventListener("DOMContentLoaded", function () {
var db = WebSQL('test.db');
console.log(db);
db.query("DROP TABLE Dictionary");
var init = "CREATE TABLE IF NOT EXISTS Dictionary(WORD varchar(255) UNIQUE, COUNT int)";
db.query(init)
        .fail(function (tx, err) {
            console.log(err);
        }).done(function (products) {
            len = products[0];
            init = "INSERT INTO Dictionary(WORD, COUNT) VALUES('the', 3030), ('to', 1754), ('of', 1332), ('and', 1158), ('that', 874), ('in', 792), ('he', 712), ('was', 679), ('his', 587), ('as', 570), ('had', 544), ('for', 465), ('be', 447), ('it', 419), ('on', 348), ('they', 348), ('with', 312), ('would', 294), ('have', 250), ('at', 248), ('you', 248), ('this', 234), ('not', 233), ('could', 213), ('up', 211), ('all', 200), ('their', 200), ('from', 199), ('been', 190), ('so', 190), ('by', 187), ('were', 182), ('when', 172), ('out', 158), ('is', 152), ('we', 148), ('what', 146), ('him', 141), ('one', 141), ('but', 135), ('or', 134), ('some', 131), ('an', 130), ('more', 128), ('any', 127), ('if', 127), ('which', 127), ('who', 126), ('them', 121), ('might', 119), ('there', 116), ('must', 113), ('did', 111), ('only', 109), ('said', 109), ('over', 108), ('time', 103), ('about', 101), ('such', 99), ('though', 95), ('do', 94), ('my', 92), ('are', 90), ('like', 90), ('no', 90), ('other', 87), ('just', 85), ('those', 85), ('get', 84), ('than', 83), ('after', 77), ('make', 77), ('can', 76), ('down', 72), ('now', 72), ('see', 72), ('how', 71), ('even', 69), ('where', 69), ('across', 68), ('being', 68), ('scout', 68), ('your', 67), ('little', 65), ('take', 64), ('way', 64), ('know', 63), ('two', 62), ('made', 60), ('us', 60), ('good', 59), ('heard', 58), ('much', 58), ('these', 58), ('upon', 58), ('will', 58), ('himself', 57), ('back', 56), ('came', 56), ('our', 56), ('while', 56), ('along', 54), ('going', 54), ('never', 54), ('very', 52), ('boys', 51), ('into', 51), ('man', 50), ('may', 50), ('me', 50), ('seemed', 50), ('then', 50), ('told', 50), ('come', 48), ('thought', 48), ('close', 47), ('same', 47), ('here', 46), ('knew', 46), ('think', 46), ('well', 46), ('give', 45), ('keep', 45), ('say', 45), ('through', 45), ('also', 44), ('because', 44), ('before', 44), ('far', 44), ('long', 44), ('once', 44), ('should', 44), ('around', 42), ('big', 41), ('go', 41), ('tell', 41), ('first', 40), ('look', 40), ('toward', 40), ('under', 40), ('fire', 39), ('saw', 39), ('boy', 38), ('every', 38), ('felt', 38), ('find', 38), ('looked', 38), ('still', 38), ('away', 37), ('thing', 37), ('believe', 36), ('old', 36), ('near', 35), ('too', 35), ('always', 34), ('enough', 34), ('half', 34), ('has', 34), ('mean', 34), ('right', 34), ('asked', 33), ('bridge', 33), ('camp', 33), ('great', 33), ('having', 33), ('its', 33), ('many', 33), ('quite', 33), ('started', 33), ('ye', 33), ('another', 32), ('anything', 32), ('eyes', 32), ('off', 32), ('hand', 31), ('mind', 31), ('most', 31), ('seen', 31), ('without', 31), ('again', 30), ('better', 30), ('sure', 30), ('train', 30), ('both', 29), ('ever', 29), ('let', 29), ('men', 29), ('things', 29), ('three', 29), ('went', 29), ('doing', 28), ('fact', 28), ('got', 28), ('line', 28), ('own', 28), ('try', 28), ('already', 27), ('hear', 27), ('making', 27), ('soon', 27), ('taken', 27), ('until', 27), ('wire', 27), ('against', 26), ('certain', 26), ('chance', 26), ('meant', 26), ('run', 26), ('able', 25), ('call', 25), ('found', 25), ('put', 25), ('ready', 25), ('sort', 25), ('trying', 25), ('best', 24), ('called', 24), ('gave', 24), ('place', 24), ('door', 23), ('guide', 23), ('kept', 23), ('ought', 23), ('part', 23), ('possibly', 23), ('pretty', 23), ('several', 23), ('turn', 23), ('turned', 23), ('whole', 23), ('between', 22), ('carried', 22), ('cut', 22), ('feeling', 22), ('heavy', 22), ('logging', 22), ('perhaps', 22), ('quickly', 22), ('hands', 21), ('hardly', 21), ('head', 21), ('last', 21), ('later', 21), ('managed', 21), ('often', 21), ('since', 21), ('times', 21), ('whose', 21), ('almost', 20), ('began', 20), ('believed', 20), ('getting', 20), ('guess', 20), ('least', 20), ('left', 20), ('others', 20), ('really', 20), ('sound', 20), ('took', 20), ('use', 20), ('want', 20), ('why', 20), ('yet', 20), ('case', 19), ('further', 19), ('given', 19), ('gone', 19), ('looking', 19), ('moose', 19), ('party', 19), ('railway', 19), ('reason', 19), ('scouts', 19), ('side', 19), ('stand', 19), ('suddenly', 19), ('trestle', 19), ('whether', 19), ('easily', 18), ('feel', 18), ('fellow', 18), ('hope', 18), ('lay', 18), ('low', 18), ('master', 18), ('object', 18), ('sent', 18), ('signs', 18), ('taking', 18), ('woods', 18), ('country', 17), ('day', 17), ('full', 17), ('happened', 17), ('heading', 17), ('light', 17), ('nothing', 17), ('poor', 17), ('show', 17), ('bound', 16), ('brought', 16), ('cause', 16), ('coming', 16), ('duty', 16), ('easy', 16), ('less', 16), ('next', 16), ('set', 16), ('thus', 16), ('young', 16), ('carry', 15), ('danger', 15), ('done', 15), ('few', 15), ('help', 15), ('likely', 15), ('longer', 15), ('lost', 15), ('need', 15), ('night', 15), ('order', 15), ('passed', 15), ('plan', 15), ('small', 15), ('terrible', 15), ('war', 15), ('assured', 14), ('behind', 14), ('bull', 14), ('closer', 14), ('each', 14), ('fairly', 14), ('fellows', 14), ('finally', 14), ('gun', 14), ('hard', 14), ('held', 14), ('hold', 14), ('inside', 14), ('leader', 14), ('leg', 14), ('minute', 14), ('pair', 14), ('rather', 14), ('reach', 14), ('reached', 14), ('remarked', 14), ('second', 14), ('short', 14), ('stout', 14), ('admitted', 13), ('aroused', 13), ('became', 13), ('border', 13), ('cat', 13), ('caused', 13), ('during', 13), ('face', 13), ('fast', 13), ('follow', 13), ('ground', 13), ('guards', 13), ('her', 13), ('hunting', 13), ('lantern', 13), ('life', 13), ('means', 13), ('occasion', 13), ('placed', 13), ('read', 13), ('sign', 13), ('trail', 13), ('wanted', 13), ('air', 12), ('bad', 12), ('bent', 12), ('bit', 12), ('burst', 12), ('caught', 12), ('chums', 12), ('cried', 12), ('days', 12), ('decided', 12), ('else', 12), ('end', 12), ('fat', 12), ('glad', 12), ('hastened', 12), ('hour', 12), ('knows', 12), ('learned', 12), ('lot', 12), ('matter', 12), ('mile', 12), ('mine', 12), ('none', 12), ('pine', 12), ('plotters', 12), ('sat', 12), ('shot', 12)";
            db.query(init)
                .fail(function (tx, err) {
                    console.log(err);
                }).done(function (products) {
                    len = products[0];
                    myKeypress();
                });
        });
document.getElementById("txtIn").addEventListener("keyup", function () {
    myKeypress();
});
function myKeypress() {
    var len = 0;
    var input = "SELECT COUNT(*) count FROM Dictionary WHERE word LIKE '" + document.getElementById("txtIn").value + "%'";
    db.query(input)
        .fail(function (tx, err) {
            console.log(err);
        }).done(function (products) {
            len = products[0].count;
        });
    input = "SELECT word FROM Dictionary WHERE word LIKE '" + document.getElementById("txtIn").value + "%' ORDER BY COUNT DESC LIMIT 5";
    console.log(input);
    db.query(input)
        .fail(function (tx, err) {
            console.log(err);
        }).done(function (products) {
            console.log(products[0]);
            document.getElementById("demo").innerHTML = "NULL";
            document.getElementById("demo1").innerHTML = "NULL";
            document.getElementById("demo2").innerHTML = "NULL";
            document.getElementById("demo3").innerHTML = "NULL";
            document.getElementById("demo4").innerHTML = "NULL";
            if (len > 0) {
                document.getElementById("demo").innerHTML = products[0].WORD;
                if (len > 1) {
                    document.getElementById("demo1").innerHTML = products[1].WORD;
                    if (len > 2) {
                        document.getElementById("demo2").innerHTML = products[2].WORD;
                        if (len > 3) {
                            document.getElementById("demo3").innerHTML = products[3].WORD;
                            if (len > 4) {
                                document.getElementById("demo4").innerHTML = products[4].WORD;
                            }
                        }
                    }
                }
            }
        });
}
function executeCopy(text) {
    console.log("Hello World");
    var input = document.createElement('textarea');
    document.body.appendChild(input);
    input.value = text;
    input.focus();
    input.select();
    document.execCommand('Copy');
    input.remove();
}
document.getElementById("demo").addEventListener("click", function () {
    executeCopy(document.getElementById("demo").innerHTML);
});
document.getElementById("demo1").addEventListener("click", function () {
    executeCopy(document.getElementById("demo1").innerHTML);
});
document.getElementById("demo2").addEventListener("click", function () {
    executeCopy(document.getElementById("demo2").innerHTML);
});
document.getElementById("demo3").addEventListener("click", function () {
    executeCopy(document.getElementById("demo3").innerHTML);
});
document.getElementById("demo4").addEventListener("click", function () {
    executeCopy(document.getElementById("demo4").innerHTML);
});
});