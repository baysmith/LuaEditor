/*	Copyright (c) 2015 SGH
**	
**	Permission is granted to use, modify and redistribute this software.
**	Modified versions of this software MUST be marked as such.
**	
**	This software is provided "AS IS". In no event shall
**	the authors or copyright holders be liable for any claim,
**	damages or other liability. The above copyright notice
**	and this permission notice shall be included in all copies
**	or substantial portions of the software.
**	
**	File created on: 22/08/2015
*/

#include "luaindenter.h"
#include "scanner/luascanner.h"

#include <texteditor/tabsettings.h>
#include <QSet>

namespace LuaEditor { namespace Internal {

enum { TAB_SIZE = 4 };

static QSet<QString> const g_increaseKeywords = {
	QStringLiteral("function"),
	QStringLiteral("do"),
	QStringLiteral("then"),
	QStringLiteral("else"),
	QStringLiteral("repeat")
};
static QSet<QString> const g_decreaseKeywords = {
    QStringLiteral("else"),
    QStringLiteral("end"),
};

LuaIndenter::LuaIndenter(){}
LuaIndenter::~LuaIndenter(){}

bool LuaIndenter::isElectricCharacter(QChar const& ch) const { return ch == QLatin1Char('{') || ch == QLatin1Char('='); }
bool LuaIndenter::isInvElectricCharacter(QChar const&) const { return false; }
void LuaIndenter::indentBlock(QTextDocument *doc, const QTextBlock &block, const QChar &typedChar, const TextEditor::TabSettings &tabSettings)
{
	Q_UNUSED(doc);
	Q_UNUSED(typedChar);
	
	QTextBlock previousBlock = block.previous();
	if(!previousBlock.isValid())
	{
		tabSettings.indentLine(block, 0);
		return;
	}
	
	QString const& previousBlockText = previousBlock.text();
    auto indent = qMax<int>(0, tabSettings.indentationColumn(previousBlockText)
                            + getLineDelta(previousBlockText, block.text())*TAB_SIZE);

	tabSettings.indentLine(block, indent);
}
QString LuaIndenter::getFirstKeyword(const QString &line) const
{
	QString firstKeyword;
	
	FormatToken thisToken;
	Scanner scannerA(line.constData(),line.size());
	while((thisToken = scannerA.read()).format() != Format_EndOfBlock)
	{
		if(thisToken.format() == Format_Keyword)
        {
			firstKeyword = scannerA.value(thisToken);
            break;
        }
	}
	return firstKeyword;
}
QString LuaIndenter::getLastKeyword(const QString &line) const
{
	QString lastKeyword;

	FormatToken thisToken;
	Scanner scannerA(line.constData(),line.size());
	while((thisToken = scannerA.read()).format() != Format_EndOfBlock)
	{
		if(thisToken.format() == Format_Keyword)
			lastKeyword = scannerA.value(thisToken);
	}
	return lastKeyword;
}
int LuaIndenter::getLineDelta(const QString& prevLine, const QString& line) const
{
    if (prevLine.length() == 0) return 0;

	// Increase indentation sooner, if possible.
	int index = prevLine.length()-1;
	while((index > 0) && prevLine[index].isSpace())
		--index;
	
	if(isElectricCharacter(prevLine[index]))
		return 1;
	
	if(isInvElectricCharacter(prevLine[index]))
		return -1;
	
    int keyword_sum = 0;
    FormatToken thisToken;
	Scanner scannerA(prevLine.constData(),prevLine.size());
	while((thisToken = scannerA.read()).format() != Format_EndOfBlock)
	{
		if(thisToken.format() == Format_Keyword)
        {
			auto keyword = scannerA.value(thisToken);
            if(g_increaseKeywords.contains(keyword))
                ++keyword_sum;

            if(g_decreaseKeywords.contains(keyword))
                --keyword_sum;
        }
	}
    if(g_decreaseKeywords.contains(getFirstKeyword(line)))
        --keyword_sum;

    if (keyword_sum == 0)
    {
        if(g_increaseKeywords.contains(getLastKeyword(prevLine)))
            return 1;
        if(g_decreaseKeywords.contains(getFirstKeyword(line)))
            return -1;
    }

    return keyword_sum;
}

} }

